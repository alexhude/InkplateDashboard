//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "Inkplate.h"

#include "config.hpp"
#include "SystemCoreDelegate.hpp"

struct SettingsFileHeader {
    uint32_t            magic;
    uint32_t            size;
    uint32_t            version;
    uint32_t            crc;
};

struct SettingsFile {
    SettingsFileHeader      header;
    uint8_t                 pinHash[0x20];
    bool                    frontlightEnabled;
    int                     frontlightLevel;
    int                     minsPerToken;
};

class View;
class Profile;
class EventManagerDelegate;
class SdFat;

class SystemCore : public SystemCoreDelegate {

public:

    SystemCore() {};
    ~SystemCore() {};

    void initSerial();
    void initInkplate();
    void initTouch();
    void initFS();
    void initTimer();

    void setEventDelegate(EventManagerDelegate* delegate);

    void handleTouch();
    void handleTimer();

    void cacheScreen();
    void restoreScreenCache();
    void doRender();

public: // SystemCoreDelegate

    const char* getInitError() override;
    void getDisplaySize(int* width, int* height) override;
    void setCurrentView(View* view) override;
    void forceFullClean(bool delay = false);
    void enableScreenCache(bool enable) override;
    bool loadSettings() override;
    bool saveSettings() override;
    bool frontlightEnabled() override;
    int  getFrontlightLevel() override;
    const char* getFrontlightLevelString() override;
    void enableFrontlightLevel(bool enable) override;
    void setFrontlightLevel(int level) override;
    int  getMinsPerToken() override;
    const char* getMinsPerTokenString() override;
    void setMinsPerToken(int minutes) override;
    bool authPIN(char* pin) override;
    bool loadProfile(int index, void* data, int* bytes) override;
    bool saveProfile(int index, void* data, int bytes) override;
    bool importProfile(int index, void* data, int* bytes, const char** errStr) override;
    bool importActivityList(int index, void* data, int* bytes, const char** errStr) override;
    const char* getDateString() override;
    const char* getTimeString() override;
    int getMinutesForDay() override;
    int getWeekDay() override;
    void setDate(const char* dateStr) override;
    void setTime(const char* timeStr) override;
    int getBatteryPercent() override;
    float getBatteryVoltage() override;
    void updatePIN(const char* pin) override;
    void factoryReset() override;

    void dumpDiagnostics() override;

private:

    static Inkplate     s_inkplate;
    static const int    s_maxRefreshCount = 10;
    
    bool                    m_fsReady = false;
    bool                    m_screenCacheEnabled = false;
    unsigned char*          m_displayCache = nullptr;

    EventManagerDelegate*   m_eventDelegate = nullptr;

    View*                   m_currentView = nullptr;
    int                     m_refreshCount = 0;

    const char*             m_initErrorStr = nullptr;

    // Settings
    char                    m_dateString[16] = {0}; // "DD/MM/YYYY"
    char                    m_timeString[16] = {0}; // "HH:MM"
    bool                    m_frontlightEnabled = false;
    int                     m_frontlightLevel = 0;
    char                    m_frontlightLevelString[5] = {0};
    float                   m_batteryVoltage = 0.0f;
    int                     m_minsPerToken = 20;
    char                    m_minsPerTokenString[5] = {0};
    uint8_t                 m_pinHash[0x20] = { // default PIN: sha256("000")
        0x2A, 0xC9, 0xA6, 0x74, 0x6A, 0xCA, 0x54, 0x3A, 0xF8, 0xDF, 0xF3, 0x98, 0x94, 0xCF, 0xE8, 0x17,
        0x3A, 0xFB, 0xA2, 0x1E, 0xB0, 0x1C, 0x6F, 0xAE, 0x33, 0xD5, 0x29, 0x47, 0x22, 0x28, 0x55, 0xEF 
    };

private:

};