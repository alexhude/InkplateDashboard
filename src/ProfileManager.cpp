//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"

#include "ProfileManager.hpp"
#include "SystemCoreDelegate.hpp"
#include "helper.hpp"

void ProfileManager::setSystemCoreDelegate(SystemCoreDelegate* delegate) {
    m_systemCoreDelegate = delegate;
}

bool ProfileManager::loadAllProfiles() {
    if (!m_systemCoreDelegate) return false;

    bool res = true;
    for (int p = 0; p < s_maxProfileCount; p++) {
        ProfileFile data = {0};
        int bytes = sizeof(ProfileFile);

        bool res = m_systemCoreDelegate->loadProfile(p, &data, &bytes);
        if (res) {
            m_profiles[p].deserializeData(&data, bytes);
        } else {
            elog("unable to load profile at index %d", p);
        }
    }
    return res;
}

bool ProfileManager::saveAllProfiles() {
    if (!m_systemCoreDelegate) return false;

    bool res = true;
    for (int p = 0; p < s_maxProfileCount; p++) {
        if (!m_profiles[p].isActive())
            continue;

        if (!m_profiles[p].isTimerActive())
            continue;

        ProfileFile data = {0};
        int bytes = 0;
        m_profiles[p].serializeData(&data, &bytes);

        bool res = m_systemCoreDelegate->saveProfile(p, &data, bytes);
        if (!res) {
            elog("unable to save profile at index %d", p);
        }
    }
    return res;
}

bool ProfileManager::loadProfile(int profileIdx) {
    if (!m_systemCoreDelegate) return false;

    if (profileIdx >=0 && profileIdx < s_maxProfileCount) {
        if (!m_profiles[profileIdx].isActive())
            return false;

        bool res = true;
        ProfileFile data = {0};
        int bytes = sizeof(ProfileFile);

        res = m_systemCoreDelegate->loadProfile(profileIdx, &data, &bytes);
        if (res) {
            m_profiles[profileIdx].deserializeData(&data, bytes);
        } else {
            elog("unable to load profile at index %d", profileIdx);
        }
        return res;
    }
    return false;
}

bool ProfileManager::saveProfile(int profileIdx) {
    if (!m_systemCoreDelegate) return false;

    if (profileIdx >=0 && profileIdx < s_maxProfileCount) {
        if (!m_profiles[profileIdx].isActive())
            return false;

        bool res = true;
        ProfileFile data = {0};
        int bytes = 0;
        m_profiles[profileIdx].serializeData(&data, &bytes);

        res = m_systemCoreDelegate->saveProfile(profileIdx, &data, bytes);
        if (!res) {
            elog("unable to save profile at index %d", profileIdx);
        }
        return res;
    }
    return false;
}

int ProfileManager::getMaxProfilesNumber() {
    return s_maxProfileCount;
}

bool ProfileManager::importProfile(int profileIdx, const char** errStr) {
    if (!m_systemCoreDelegate) return false;

    if (profileIdx >=0 && profileIdx < s_maxProfileCount) {
        bool res = true;
        char* data = (char*)malloc(MAX_FILE_SIZE_PROFILE + 1);
        if (!data) {
            elog("unable to alloc memory (%d)", MAX_FILE_SIZE_PROFILE + 1);
            return false;
        }
        int bytes = MAX_FILE_SIZE_PROFILE;
        res = m_systemCoreDelegate->importProfile(profileIdx, data, &bytes, errStr);
        if (res) {
            data[bytes] = '\0';
            res = m_profiles[profileIdx].importProfile(data, bytes+1, errStr);
        }
        if (!res) {
            elog("unable to import profile at index %d (%s)", profileIdx, (errStr)? (*errStr)? *errStr : "?" : "?");
        }
        free(data);
        return res;
    }

    return false;
}

bool ProfileManager::importActivityList(int profileIdx, const char** errStr) {
    if (!m_systemCoreDelegate) return false;

    if (profileIdx >=0 && profileIdx < s_maxProfileCount) {
        if (!m_profiles[profileIdx].isActive()) {
            *errStr = "Profile is not active";
            return false;
        }

        bool res = true;
        char* data = (char*)malloc(MAX_FILE_SIZE_ACTIVITY_LIST + 1);
        if (!data) {
            elog("unable to alloc memory (%d)", MAX_FILE_SIZE_ACTIVITY_LIST + 1);
            return false;
        }
        int bytes = MAX_FILE_SIZE_ACTIVITY_LIST;
        res = m_systemCoreDelegate->importActivityList(profileIdx, data, &bytes, errStr);
        if (res) {
            data[bytes] = '\0';
            res = m_profiles[profileIdx].importActivityList(data, bytes+1, errStr);
        }
        if (!res) {
            elog("unable to import activity list at index %d (%s)", profileIdx, (errStr)? (*errStr)? *errStr : "?" : "?");
        }
        free(data);
        return res;
    }

    return false;
}

bool ProfileManager::isActive(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        return m_profiles[profileIdx].isActive();
    return false;
}

void ProfileManager::tickMinute() {
    for (int p = 0; p < s_maxProfileCount; p++) {
        if (!m_profiles[p].isActive()) continue;
        m_profiles[p].tickMinute();
    }
}

void ProfileManager::tickWeek() {
    for (int p = 0; p < s_maxProfileCount; p++) {
        if (!m_profiles[p].isActive()) continue;
        m_profiles[p].tickWeek();
    }
}

void ProfileManager::enableTimer(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            m_profiles[profileIdx].enableTimer();
}

void ProfileManager::disableTimer(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            m_profiles[profileIdx].disableTimer();
}

const char* ProfileManager::getName(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].getName();
    return nullptr;
}

int ProfileManager::getTotalTime(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].getTotalTime();
    return 0;
}

const char* ProfileManager::getTotalTimeString(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].getTotalTimeString();
    return nullptr;
}

void ProfileManager::setTotalTime(int profileIdx, int time) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].setTotalTime(time);
}

int ProfileManager::getRemainTime(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].getRemainTime();
    return 0;
}

int ProfileManager::getSessionTime(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].getSessionTime();
    return -1;
}

void ProfileManager::addMinutes(int profileIdx, int minutes) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            m_profiles[profileIdx].addMinutes(minutes);
}

void ProfileManager::removeMinutes(int profileIdx, int minutes) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            m_profiles[profileIdx].removeMinutes(minutes);
}

bool ProfileManager::tokenTypeRequested(int profileIdx, TokenType type) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].tokenTypeRequested(type);
    return 0;
}

void ProfileManager::requestToken(int profileIdx, TokenType type) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].requestToken(type);
}

void ProfileManager::cancelTokenRequest(int profileIdx, TokenType type) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].cancelTokenRequest(type);
}

void ProfileManager::approveTokenRequest(int profileIdx, TokenType type) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].approveTokenRequest(type);
}

void ProfileManager::covertTokenToMins(int profileIdx, int minutes) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].covertTokenToMins(minutes);
}

int ProfileManager::getTokens(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].getTokens();
    return 0;
}

const char* ProfileManager::getTokensString(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].getTokensString();
    return nullptr;
}

bool ProfileManager::getActivity(int profileIdx, int actIdx, int* time, const char** text, int weekDay) {
    if (!m_systemCoreDelegate) return false;

    if (profileIdx >=0 && profileIdx < s_maxProfileCount) {
        if (m_profiles[profileIdx].isActive()) {
            int wd = m_systemCoreDelegate->getWeekDay();
            if (weekDay != -1)
                wd = weekDay;
            return m_profiles[profileIdx].getActivity(wd, actIdx, time, text);
        }
    }
    return false;
}

void ProfileManager::factoryReset() {
    // TODO: implement
}

void ProfileManager::clearAllActivities(int profileIdx) {
    if (profileIdx >=0 && profileIdx < s_maxProfileCount)
        if (m_profiles[profileIdx].isActive())
            return m_profiles[profileIdx].clearAllActivities();
}

void ProfileManager::dumpDiagnostics() {
    dlog("ProfileManager:");
    for (int p=0; p < s_maxProfileCount; p++) {
        dlog("  [%2d] active = %d", p, m_profiles[p].isActive());
        if (m_profiles[p].isActive()) {
            dlog("       name = '%s'", m_profiles[p].getName());
            dlog("       totalTime = %d", m_profiles[p].getTotalTime());
            dlog("       totalTimeString = '%s'", m_profiles[p].getTotalTimeString());
            dlog("       remainTime = %d", m_profiles[p].getRemainTime());
            dlog("       tokenRequests:");
            for (int t = 0; t < TokenType::Count; t++) {
                dlog("         [%d] %s", t, (m_profiles[p].tokenTypeRequested(TokenType(t)))? "pending" : "none");
            }
            dlog("       tokens = %d", m_profiles[p].getTokens());
            dlog("       tokensString = '%s'", m_profiles[p].getTokensString());
            dlog("       timerActive = %d", m_profiles[p].isTimerActive());
            dlog("       activities:");

            const char* weekDayStr[7] = {
                "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
            };
            for (int w = 0; w < 7; w++) {
                int time = 0;
                const char* text = nullptr;
                if (!m_profiles[p].getActivity(w, 0, &time, &text))
                    continue;
                dlog("         [%d] %s", w, (w >= 0 && w <= 6)? weekDayStr[w] : "Unk");
                for (int a = 0; a < 10; a++) {
                    if (!m_profiles[p].getActivity(w, a, &time, &text))
                        break;
                    dlog("             [%d] time = %.2d:%.2d '%s'", a, time/60, time%60, text);
                }
            }
        }
    }
}
