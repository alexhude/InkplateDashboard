//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "SdFat.h"

#include "SystemCore.hpp"
#include "View.hpp"
#include "EventManagerDelegate.hpp"
extern "C" {
    #include "sha256.h"
    #include "crc32.h"
}

#include "helper.hpp"

static const uint32_t s_settingsFileMagic = 'D@SS';
static const uint32_t s_settingsFileVersion = FW_VERSION;

Inkplate SystemCore::s_inkplate(INKPLATE_1BIT);

void SystemCore::initSerial() {
    Serial.begin(115200);
    Serial.println("[+] serial output ready");
    Logger* logger = Logger::getInstance();
    if (logger)
        logger->enable();
}

void SystemCore::initInkplate() {
    s_inkplate.begin();
    s_inkplate.clearDisplay();
    s_inkplate.display();

#if BOARD_HAS_PSRAM
    if (psramInit()) {
        dlog("PSRAM ready:");
        dlog("  heap total:  %d", ESP.getHeapSize());
        dlog("  heap free:   %d", ESP.getFreeHeap());
        dlog("  PSRAM total: %d", ESP.getPsramSize());
        dlog("  PSRAM free:  %d", ESP.getFreePsram());
    } else {
        elog("unable to init PSRAM");
    }
#endif

    m_displayCache = (unsigned char*)malloc(E_INK_WIDTH * E_INK_HEIGHT / 8);
    memset(m_displayCache, 0, E_INK_WIDTH * E_INK_HEIGHT / 8);
    dlog("inkplate ready");
}

void SystemCore::initTouch() {
    if (!s_inkplate.tsInit(true)) {
        elog("unable to init touch controller!");
        m_initErrorStr = "Unable to init\ntouch controller!";
    } else {
        dlog("touch controller ready");
    }
}

void SystemCore::initFS() {
    if(!s_inkplate.sdCardInit()) {
        elog("unable to init SD card!");
        m_initErrorStr = "Unable to init\nSD card!";
        return;
    }
    dlog("SD card (filesystem) ready");
    m_fsReady = true;

    SdFat fat = s_inkplate.getSdFat();
    char path[64] = {0};

    sprintf(path, "/Settings");
    if (!fat.open(path, O_RDONLY)) {
        elog("unable find Settings directory!");

        if (!fat.mkdir(path, true)) {
            elog("unable create Settings directory!");
            m_initErrorStr = "Unable to create\n'/Settings' directory!";
            return;
        } else {
            dlog("/Settings directory created");
            saveSettings();
        }
    }

    sprintf(path, "/Profiles");
    if (!fat.open(path, O_RDONLY)) {
        elog("unable find Profiles directory!");

        
        if (!fat.mkdir(path, true)) {
            elog("unable create Profiles directory!");
            m_initErrorStr = "Unable to create\n'/Profiles' directory!";
            return;
        } else {
            dlog("/Profiles directory created");
        }
    }
}

void SystemCore::initTimer() {
    /*   source_clock
     *       Inkplate::TIMER_CLOCK_4096HZ     -> clk = 4096Hz -> min timer = 244uS -> MAX timer = 62.256mS
     *       Inkplate::TIMER_CLOCK_64HZ       -> clk = 64Hz   -> min timer = 15.625mS -> MAX timer = 3.984s
     *       Inkplate::TIMER_CLOCK_1HZ        -> clk = 1Hz    -> min timer = 1s -> MAX timer = 255s
     *       Inkplate::TIMER_CLOCK_1PER60HZ   -> clk = 1/60Hz -> min timer = 60s -> MAX timer = 4h15min
     *   value
     *       coundowntime in seconds
     *   int_enable
     *       true = enable interrupt; false = disable interrupt
     *   int_pulse
     *       true = interrupt generate a pulse; false = interrupt follows timer flag
     */
    s_inkplate.rtcTimerSet(Inkplate::TIMER_CLOCK_1HZ, 1, false, false);
    dlog("timer ready");

    dlog("current time: %d:%d:%d %d/%d/%d (%d)", 
        s_inkplate.rtcGetHour(),
        s_inkplate.rtcGetMinute(),
        s_inkplate.rtcGetSecond(),
        s_inkplate.rtcGetDay(),
        s_inkplate.rtcGetMonth(),
        s_inkplate.rtcGetYear(),
        s_inkplate.rtcGetWeekday()
    );    
}

void SystemCore::setEventDelegate(EventManagerDelegate* delegate) {
    m_eventDelegate = delegate;
}

const char* SystemCore::getInitError() {
    return m_initErrorStr;
}

void SystemCore::getDisplaySize(int* width, int* height) {
    if (width)
        *width = s_inkplate.width();

    if (height)
        *height = s_inkplate.height();
}

void SystemCore::handleTouch() {
    if (!m_currentView) return;

    if (m_currentView->touch(&s_inkplate)) {
        doRender();
    }
}

void rtcClearTimerFlag()
{
    uint8_t _crtl_2;

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_CTRL_2);
    Wire.endTransmission();
    Wire.requestFrom(I2C_ADDR, 1);

    _crtl_2 = Wire.read() & ~(RTC_TIMER_FLAG);

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_CTRL_2);
    Wire.write(_crtl_2);
    Wire.endTransmission();
}

void SystemCore::handleTimer() {
    static int oneMin = 60;
    static int tenMin = 600;
    static int weekDay = -1;

    if (s_inkplate.rtcCheckTimerFlag()) {
        rtcClearTimerFlag();
        if (!oneMin) {
            vlog("SystemCore::handleTimer(min)");
            if (m_eventDelegate)
                m_eventDelegate->tickMinute();
            doRender();
            oneMin = 60;
        } else {
            oneMin--;
        }

        if (!tenMin) {
            vlog("SystemCore::handleTimer(10min)");
            if (m_eventDelegate)
                m_eventDelegate->profileSaveAll();
            tenMin = 600;
        } else {
            tenMin--;
        }
    }

    int newWeekDay = s_inkplate.rtcGetWeekday();
    // track Sunday to Monday switch
    if (weekDay == 0 && newWeekDay == 1) {
        if (m_eventDelegate) {
            m_eventDelegate->tickWeek();
            m_eventDelegate->profileSaveAll();
        }
    }
    weekDay = newWeekDay;
}

void SystemCore::cacheScreen() {
    memcpy(m_displayCache, s_inkplate._partial, E_INK_WIDTH * E_INK_HEIGHT / 8);
}

void SystemCore::restoreScreenCache() {
    memcpy(s_inkplate._partial, m_displayCache, E_INK_WIDTH * E_INK_HEIGHT / 8);
}

void SystemCore::doRender() {
    if (!m_currentView) return;

    if (m_screenCacheEnabled) {
        vlog("SystemCore cache restored");
        restoreScreenCache();
    } else {
        s_inkplate.clearDisplay();
    }

    bool forceCache = m_currentView->render(&s_inkplate);

    if (forceCache) {
        m_screenCacheEnabled = true;
        cacheScreen();
    }

    s_inkplate.einkOn();
    if (m_refreshCount == s_maxRefreshCount) {
        s_inkplate.einkOff();
        s_inkplate.display();
        m_refreshCount = 0;
    }
    else {
        s_inkplate.partialUpdate(false, true);
        m_refreshCount++;
    }
}

void SystemCore::setCurrentView(View* view) {
    if (m_currentView != view) {
        m_currentView = view;
        forceFullClean();
    }
}

void SystemCore::forceFullClean(bool delay) {
    m_refreshCount = s_maxRefreshCount;
    if (delay)
        m_refreshCount--;
}

void SystemCore::enableScreenCache(bool enable) {
    m_screenCacheEnabled = enable;
}

bool SystemCore::loadSettings() {
    if (!m_fsReady) return false;

    SettingsFile settings;
    int bytes = sizeof(SettingsFile);

    char path[64] = {0};
    sprintf(path, "Settings/settings.bin");

    SdFile file; 
    if (!file.open(path, O_RDONLY)) {
        elog("unable to open file %s", path);
        m_initErrorStr = "Unable to open Settings file";
        return false;
    }

    int size = file.fileSize();
    if (size > bytes) {
        elog("file to big %d (expected %d)", size, bytes);
        return false;
    }

    if (file.read(&settings, size) != size) {
        elog("unable to read file %s (%d bytes)", path, size);
        return false;
    }

    file.close();

    vlog("settings loaded from %s (%d bytes)", path, size);

    if (settings.header.magic != s_settingsFileMagic) { 
        elog("unable to parse settings: invalid magic %.8X", settings.header.magic);
        return false;
    }

    if (settings.header.version == s_settingsFileVersion) {
        if (bytes < sizeof(SettingsFile)) {
            elog("unable to parse settings: invalid size (%d bytes, %d expected)", bytes, settings.header.size);
            return false;
        }

        if (settings.header.size < sizeof(SettingsFile)) {
            elog("unable to parse settings: invalid header size (%d bytes, %d expected)", settings.header.size, settings.header.size);
            return false;
        }
        
        uint32_t crc = crc32((uint8_t*)&settings + sizeof(SettingsFileHeader), sizeof(SettingsFile) - sizeof(SettingsFileHeader));
        if (settings.header.crc != crc)  {
            elog("unable to parse settings: invalid CRC (%.8X, %.8X expected)", crc, settings.header.crc);
            return false;
        }

        s_inkplate.setFrontlight(0);
        m_frontlightEnabled = settings.frontlightEnabled;
        m_frontlightLevel = settings.frontlightLevel;
        sprintf(m_frontlightLevelString, "%d%%", m_frontlightLevel);
        if (m_frontlightEnabled) {
            setFrontlightLevel(m_frontlightLevel);
        }
        m_minsPerToken = settings.minsPerToken;
        sprintf(m_minsPerTokenString, "%d", m_minsPerToken);
        memcpy(m_pinHash, settings.pinHash, SHA256_BLOCK_SIZE);
    } else {
        elog("unable to parse settings: invalid version %.8X", settings.header.version);
        return false;
    }    

    return true;
}

bool SystemCore::saveSettings() {
    if (!m_fsReady) return false;

    SettingsFile settings;
    int bytes = sizeof(SettingsFile);

    settings.header.magic = s_settingsFileMagic;
    settings.header.version = s_settingsFileVersion;
    settings.header.size = sizeof(SettingsFile);

    memcpy(settings.pinHash, m_pinHash, SHA256_BLOCK_SIZE);
    settings.frontlightEnabled = m_frontlightEnabled;
    settings.frontlightLevel = m_frontlightLevel;
    settings.minsPerToken = m_minsPerToken;

    settings.header.crc = crc32((uint8_t*)&settings + sizeof(SettingsFileHeader), sizeof(SettingsFile) - sizeof(SettingsFileHeader));

    char path[64] = {0};
    sprintf(path, "Settings/settings.bin");

    SdFile file; 
    if (!file.open(path, O_RDWR | O_CREAT)) {
        elog("unable to open file %s", path);
        return false;
    }

    if (file.write(&settings, bytes) != bytes) {
        elog("unable to write file %s (%d bytes)", path, bytes);
        return false;
    }

    file.close();

    vlog("settings saved at %s (%d bytes)", path, bytes);
    return true;
}

bool SystemCore::frontlightEnabled() {
    return m_frontlightEnabled;
}

int SystemCore::getFrontlightLevel() {
    return m_frontlightLevel;
}

const char* SystemCore::getFrontlightLevelString() {
    return m_frontlightLevelString;
}

void SystemCore::enableFrontlightLevel(bool enable) {
    if (enable) {
        int value = (IP6P_HW_FRONTLIGHT_MAX * m_frontlightLevel) / 100;
        vlog("SystemCore::setFrontlightLevel(%d -> %d)", m_frontlightLevel, value);
        if (value >= IP6P_HW_FRONTLIGHT_MIN && value <= IP6P_HW_FRONTLIGHT_MAX) {
            s_inkplate.setFrontlight(value);
        }
    } else {
        s_inkplate.setFrontlight(0);
    }
    m_frontlightEnabled = enable;
}

void SystemCore::setFrontlightLevel(int level) {
    if (!m_frontlightEnabled) return;
    if (level < 0) return;
    if (level > 100) return;

    int value = (IP6P_HW_FRONTLIGHT_MAX * level) / 100;
    vlog("SystemCore::setFrontlightLevel(%d -> %d)", level, value);
    if (value >= IP6P_HW_FRONTLIGHT_MIN && value <= IP6P_HW_FRONTLIGHT_MAX) {
        s_inkplate.setFrontlight(value);
        sprintf(m_frontlightLevelString, "%d%%", level);
        m_frontlightLevel = level;
    }
}

int SystemCore::getMinsPerToken() {
    return m_minsPerToken;
}

void SystemCore::setMinsPerToken(int minutes) {
    if (minutes > 0 && minutes < 999) {
        m_minsPerToken = minutes;
        sprintf(m_minsPerTokenString, "%d", m_minsPerToken);
    }
}

const char* SystemCore::getMinsPerTokenString() {
    return m_minsPerTokenString;   
}

bool SystemCore::authPIN(char* pin) {

    uint8_t out_hash[SHA256_BLOCK_SIZE] = {0};

	SHA256_CTX ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, (const uint8_t*)pin, strlen(pin));
	sha256_final(&ctx, out_hash);

    return memcmp(m_pinHash, out_hash, SHA256_BLOCK_SIZE) == 0;
}

bool SystemCore::loadProfile(int index, void* data, int* bytes) {
    if (!m_fsReady) return false;
    if (!data) return false;
    if (!bytes) return false;

    char path[64] = {0};
    sprintf(path, "Profiles/profile%.2d.bin", index);

    SdFile file; 
    if (!file.open(path, O_RDONLY)) {
        elog("unable to open file %s", path);
        return false;
    }

    int size = file.fileSize();
    if (size > *bytes) {
        elog("file to big %d (expected %d)", size, *bytes);
        return false;
    }

    if (file.read(data, size) != size) {
        elog("unable to read file %s (%d bytes)", path, size);
        return false;
    }

    file.close();

    vlog("profile loaded from %s (%d bytes)", path, size);

    return true;
}

bool SystemCore::saveProfile(int index, void* data, int bytes) {
    if (!m_fsReady) return false;
    if (!data) return false;
    if (!bytes) return false;

    char path[64] = {0};
    sprintf(path, "Profiles/profile%.2d.bin", index);

    SdFile file; 
    if (!file.open(path, O_RDWR | O_CREAT)) {
        elog("unable to open file %s", path);
        return false;
    }

    if (file.write(data, bytes) != bytes) {
        elog("unable to write file %s (%d bytes)", path, bytes);
        return false;
    }

    file.close();

    vlog("profile saved at %s (%d bytes)", path, bytes);

    return true;
}

bool SystemCore::importProfile(int index, void* data, int* bytes, const char** errStr) {
    if (!m_fsReady) return false;
    if (!data) return false;
    if (!bytes) return false;

    char path[64] = {0};
    sprintf(path, "profile%.2d.txt", index);

    SdFile file; 
    if (!file.open(path, O_RDONLY)) {
        *errStr = "txt file missing";
        elog("unable to open file %s", path);
        return false;
    }

    int size = file.fileSize();
    if (size > *bytes) {
        *errStr = "file too big";
        elog("file to big %d (expected %d)", size, *bytes);
        return false;
    }

    if (file.read(data, size) != size) {
        *errStr = "unable to read file";
        elog("unable to read file %s (%d bytes)", path, size);
        return false;
    }

    file.close();

    *bytes = size;
    vlog("profile import loaded from %s (%d bytes)", path, *bytes);
    return true;   
}

bool SystemCore::importActivityList(int index, void* data, int* bytes, const char** errStr) {
    if (!m_fsReady) return false;
    if (!data) return false;
    if (!bytes) return false;

    char path[64] = {0};
    sprintf(path, "activity%.2d.txt", index);

    SdFile file; 
    if (!file.open(path, O_RDONLY)) {
        *errStr = "txt file missing";
        elog("unable to open file %s", path);
        return false;
    }

    int size = file.fileSize();
    if (size > *bytes) {
        *errStr = "file too big";
        elog("file to big %d (expected %d)", size, *bytes);
        return false;
    }

    if (file.read(data, size) != size) {
        *errStr = "unable to read file";
        elog("unable to read file %s (%d bytes)", path, size);
        return false;
    }

    file.close();

    *bytes = size;
    vlog("activity list import loaded from %s (%d bytes)", path, *bytes);
    return true;   
}

const char* SystemCore::getDateString() {
    int w = s_inkplate.rtcGetWeekday();
    int d = s_inkplate.rtcGetDay();
    int m = s_inkplate.rtcGetMonth();
    int y = s_inkplate.rtcGetYear();

    const char* wstr[7] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };

    sprintf(m_dateString, "%s(%d) %.2d/%.2d/%.2d",  wstr[w], w, d, m, y - RTC_YEAR_BASE);

    return m_dateString;
}

const char* SystemCore::getTimeString() {
    int mn = s_inkplate.rtcGetMinute();
    int hr = s_inkplate.rtcGetHour();

    sprintf(m_timeString, "%.2d:%.2d", hr, mn);
    return m_timeString;
}

int SystemCore::getMinutesForDay() {
    int h = s_inkplate.rtcGetHour();
    int m = s_inkplate.rtcGetMinute();
    return (h * 60) + m;
}

int SystemCore::getWeekDay() {
    int w = s_inkplate.rtcGetWeekday();
    return w;
}

void SystemCore::setDate(const char* dateStr) {
    // format: WDDMMYY
    uint8_t w = dateStr[0] - '0';
    uint8_t d = ((dateStr[1] - '0') * 10) + (dateStr[2] - '0');
    uint8_t m = ((dateStr[3] - '0') * 10) + (dateStr[4] - '0');
    uint16_t y = RTC_YEAR_BASE + ((dateStr[5] - '0') * 10) + (dateStr[6] - '0');
    
    if (! (w >= 0 && w <= 6)) return;
    if (! (d >= 1 && d <= 31)) return;
    if (! (m >= 1 && m <= 12)) return;
    if (! (y >= 0)) return;

    dlog("set date: %d %.2d/%.2d/%.4d", w, d, m, y);
    s_inkplate.rtcSetDate(w, d, m, y);
}

void SystemCore::setTime(const char* timeStr) {
    // format: HHMM
    uint8_t h = ((timeStr[0] - '0') * 10) + (timeStr[1] - '0');
    uint8_t m = ((timeStr[2] - '0') * 10) + (timeStr[3] - '0');
    
    if (! (h >= 0 && h < 24)) return;
    if (! (m >= 0 && m < 60)) return;

    dlog("set time: %.2d:%.2d", h, m);
    s_inkplate.rtcSetTime(h, m, 00);
}

int SystemCore::getBatteryPercent() {
    // 0%   =  3.3V
    // 100% =  4.7V

    float voltage = s_inkplate.readBattery();
    m_batteryVoltage = voltage;

    if (voltage < 3.3f)
        voltage = 3.3f;
    if (voltage > 4.7f)
        voltage = 4.7f;

    voltage -= 3.3f;
    int level = (int)ceilf((voltage / (4.7 - 3.3)) * 100.0f);
    return level; 
}

float SystemCore::getBatteryVoltage() {
    float voltage = s_inkplate.readBattery();
    m_batteryVoltage = voltage;
    return m_batteryVoltage; 
}

void SystemCore::updatePIN(const char* pin) {
	SHA256_CTX ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, (const uint8_t*)pin, strlen(pin));
	sha256_final(&ctx, m_pinHash);
}

void SystemCore::factoryReset() {
    
}

void SystemCore::dumpDiagnostics() {
    dlog("SystemCore:");
    dlog("  m_fsReady = %d", m_fsReady);
    dlog("  m_screenCacheEnabled = %d", m_screenCacheEnabled);
    dlog("  m_currentView = '%s'", (m_currentView)? m_currentView->getName() : "nullptr");
    dlog("  m_refreshCount = %d of %d", m_refreshCount, s_maxRefreshCount);
    dlog("  m_frontlightLevel = %d", m_frontlightLevel); 
    dlog("  m_batteryVoltage = %f", m_batteryVoltage);
#if BOARD_HAS_PSRAM
    dlog("  heap total = %d", ESP.getHeapSize());
    dlog("  heap free = %d", ESP.getFreeHeap());
    dlog("  PSRAM total = %d", ESP.getPsramSize());
    dlog("  PSRAM free = %d", ESP.getFreePsram());
#endif
}