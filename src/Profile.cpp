//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "string.h"
#include "stdio.h"

#include "Profile.hpp"
#include "helper.hpp"

extern "C" {
    #include "crc32.h"
}

#define TimeToDayMins(h, m) ((h * 60) + m)

static const uint32_t s_profileFileMagic = 'D@SP';
static const uint32_t s_profileFileVersion = FW_VERSION;

bool Profile::isActive() {
    return m_active;
}

char* Profile::getName() {
    return m_name;
}

int Profile::getTotalTime() {
    return m_totalTime;
}

char* Profile::getTotalTimeString() {
    return m_totalTimeString;
}

int Profile::getRemainTime() {
    return m_remainTime;
}

int Profile::getSessionTime() {
    return m_sessionTime;
}

void Profile::addMinutes(int minutes) {
    m_remainTime += minutes;
}

void Profile::removeMinutes(int minutes) {
    if (m_remainTime < minutes)
        minutes = m_remainTime;
    m_remainTime -= minutes;
}

int Profile::getTokens() {
    return m_tokens;
}

char* Profile::getTokensString() {
    return m_tokensString;
}

void Profile::setName(char* name) {
    strncpy(m_name, name, s_maxStringLength);
}

void Profile::setTotalTime(int minutes) {
    m_totalTime = minutes;
    sprintf(m_totalTimeString, "%.3d", m_totalTime);
}

void Profile::setRemainTime(int minutes) {
    m_remainTime = minutes;
}

bool Profile::tokenTypeRequested(TokenType type) {
    if (type < TokenType::Count)
        return m_tokenRequested[type];
    else
        return false;
}

void Profile::requestToken(TokenType type) {
    if (type < TokenType::Count) {
        m_tokenRequested[type] = true;
    }
}

void Profile::cancelTokenRequest(TokenType type) {
    if (type < TokenType::Count) {
        m_tokenRequested[type] = false;
    }
}

void Profile::approveTokenRequest(TokenType type) {
    if (type < TokenType::Count) {
        m_tokenRequested[type] = false;
        if(m_tokens < s_maxTokenCount) {
            m_tokens++;
            sprintf(m_tokensString, "%d", m_tokens);
        } 
    }
}

void Profile::covertTokenToMins(int minutes) {
    if (m_tokens == 0)
        return;
    
    m_tokens--;
    sprintf(m_tokensString, "%d", m_tokens);
    addMinutes(minutes);
}

bool Profile::getActivity(int weekDay, int actIdx, int* time, const char** text) {
    if (weekDay >= 0 && weekDay <= 6) {
        ProfileActivityEntry* entry = &m_activityList[weekDay][actIdx];
        if (!entry->valid)
            return false;
        *time = entry->time;
        *text = entry->activity;
        return true;
    }
    return false;
}

void Profile::clearAllActivities() {
    memset(m_activityList, 0, sizeof(ProfileActivityEntry) * 7 * s_maxEntriesPerDay);
}

bool Profile::isTimerActive() {
    return m_timerActive;
}

void Profile::enableTimer() {
    m_timerActive = true;
    m_sessionTime = 0;
}

void Profile::disableTimer() {
    m_sessionTime = -1;
    m_timerActive = false;
}

void Profile::tickMinute() {
    if (!m_timerActive) return;

    if (m_remainTime > 0) {
        m_remainTime--;
        m_sessionTime++;
    }
}

void Profile::tickWeek() {
    m_remainTime = m_totalTime;
    if (m_timerActive)
        m_sessionTime = 0;
    else
        m_sessionTime = -1;
}

void Profile::serializeData(void* data, int* bytes) {
    if (!data) return;
    if (!bytes) return;

    ProfileFile* profile = (ProfileFile*)data;

    profile->header.magic = s_profileFileMagic;
    profile->header.version = s_profileFileVersion;
    profile->header.size = sizeof(ProfileFile);
    strncpy(profile->name, m_name, s_maxStringLength);
    profile->totalTime = m_totalTime;
    profile->remainTime = m_remainTime;
    profile->tokens = m_tokens;
    memcpy(profile->tokenRequested, m_tokenRequested, sizeof(m_tokenRequested));
    memcpy(profile->activityList, m_activityList, sizeof(ProfileActivityEntry) * 7 * s_maxEntriesPerDay);

    profile->header.crc = crc32((uint8_t*)data + sizeof(ProfileFileHeader), sizeof(ProfileFile) - sizeof(ProfileFileHeader));

    *bytes = sizeof(ProfileFile);
}

bool Profile::deserializeData(void* data, int bytes) {
    if (!data) return false;
    
    if (bytes < sizeof(uint32_t)) {
        elog("unable to parse profile: file too small (%d bytes)", bytes);
        return false;
    }

    ProfileFile* profile = (ProfileFile*)data;

    if (profile->header.magic != s_profileFileMagic) { 
        elog("unable to parse profile: invalid magic %.8X", profile->header.magic);
        return false;
    }

    if (bytes < sizeof(ProfileFileHeader)) {
        elog("unable to parse profile: header too small (%d bytes)", bytes);
        return false;
    }

    if (profile->header.version == s_profileFileVersion) {
        if (bytes < sizeof(ProfileFile)) {
            elog("unable to parse profile: invalid size (%d bytes, %d expected)", bytes, profile->header.size);
            return false;
        }

        if (profile->header.size < sizeof(ProfileFile)) {
            elog("unable to parse profile: invalid header size (%d bytes, %d expected)", profile->header.size, profile->header.size);
            return false;
        }
        
        uint32_t crc = crc32((uint8_t*)data + sizeof(ProfileFileHeader), sizeof(ProfileFile) - sizeof(ProfileFileHeader));
        if (profile->header.crc != crc)  {
            elog("unable to parse profile: invalid CRC (%.8X, %.8X expected)", crc, profile->header.crc);
            return false;
        }

        strncpy(m_name, profile->name, s_maxStringLength);
        m_totalTime = profile->totalTime;
        sprintf(m_totalTimeString, "%.3d", m_totalTime);
        m_remainTime = profile->remainTime;
        m_tokens = profile->tokens;
        sprintf(m_tokensString, "%d", m_tokens);

        memcpy(m_tokenRequested, profile->tokenRequested, sizeof(m_tokenRequested));
        memcpy(m_activityList, profile->activityList, sizeof(ProfileActivityEntry) * 7 * s_maxEntriesPerDay);
    } else {
        elog("unable to parse profile: invalid version %.8X", profile->header.version);
        return false;
    }

    m_active = true;

    return true;
}

bool Profile::importProfile(char* data, int bytes, const char** errStr) {
    bool res = false;

    char* cur = data;
    int bleft = bytes;

    bool sectionFound = false;
    char name[s_maxStringLength] = {0};
    unsigned int h=0;
    unsigned int m=0;
    bool seekEOL = false;

    while(bleft) {
        // find end of line
        if (seekEOL) {
            if(*cur == '\n') {
                seekEOL = false;
            }

            cur++;
            bleft--;
            continue;
        } 
        
        // skip empty line
        if(*cur == '\n') {
            cur++;
            bleft--;
            continue;
        }

        if (bleft < 9) break;

        // process profile header
        if (strncmp(cur, "[Profile]", 9) == 0) {
            sectionFound = true;
            seekEOL = true;
            continue;
        }

        int sres = 0;

        // process profile data
        if (sectionFound) {
            sres = sscanf(cur, "name=%31[^\t\n]", name);
            if (sres == 1) {
                strncpy(m_name, name, s_maxStringLength-1);
                seekEOL = true;
                continue;
            }

            sres = sscanf(cur, "ttime=%2u:%2u", &h, &m);
            if (sres == 2) {
                if (h < 23 && m < 60) {
                    m_totalTime = (h * 60) + m;
                    sprintf(m_totalTimeString, "%.3d", m_totalTime);
                    res = true;
                }
                seekEOL = true;
                continue;
            }
        } 

        seekEOL = true;
    }

    if (!res) {
        *errStr = "Entry not found (invalid format?)";
    } else {
        if (m_active == false) {
            m_remainTime = m_totalTime;
            m_tokens = 0;
            sprintf(m_tokensString, "%d", m_tokens);
            m_active = true;
        }
    }

    return res;
}

bool Profile::importActivityList(char* data, int bytes, const char** errStr) {
    bool res = false;

    char* cur = data;
    int bleft = bytes;

    char weekDay[10] = {0};
    int weekDayIdx = -1;
    unsigned int h=0;
    unsigned int m=0;
    char activity[s_maxStringLength] = {0};
    int activityIdx = -1;

    bool seekEOL = false;

    while(bleft) {
        // find end of line
        if (seekEOL) {
            if(*cur == '\n') {
                seekEOL = false;
            }

            cur++;
            bleft--;
            continue;
        } 
        
        // skip empty line
        if(*cur == '\n') {
            cur++;
            bleft--;
            continue;
        }

        if (bleft < 4) break;

        int sres = 0;
        // process week header
        sres = sscanf(cur, "[%3s", weekDay);
        if (sres == 1) {
            if (strncmp(weekDay, "Mon", 3) == 0) {
                weekDayIdx = 1;
            } else if (strncmp(weekDay, "Tue", 3) == 0) {
                weekDayIdx = 2;
            } else if (strncmp(weekDay, "Wed", 3) == 0) {
                weekDayIdx = 3;
            } else if (strncmp(weekDay, "Thu", 3) == 0) {
                weekDayIdx = 4;
            } else if (strncmp(weekDay, "Fri", 3) == 0) {
                weekDayIdx = 5;
            } else if (strncmp(weekDay, "Sat", 3) == 0) {
                weekDayIdx = 6;
            } else if (strncmp(weekDay, "Sun", 3) == 0) {
                weekDayIdx = 0;
            } else {
                elog("unknown week day: %3s", weekDay);
            }

            if (weekDayIdx != -1) {
                activityIdx = 0;
            }

            seekEOL = true;
            continue;
        }

        // process activity entry
        if (weekDayIdx != -1) {
            if (bleft < 7) break;

            sres = sscanf(cur, "%2u:%2u|%31[^\t\n]", &h, &m, activity);
            if (sres == 3) {
                if (h < 23 && m < 60) {
                    if (!res) {
                        // first good entry, clear entire list
                        memset(m_activityList, 0, sizeof(ProfileActivityEntry) * 7 * s_maxEntriesPerDay);
                    }

                    m_activityList[weekDayIdx][activityIdx].valid = true;
                    m_activityList[weekDayIdx][activityIdx].time = (h * 60) + m;
                    strncpy(m_activityList[weekDayIdx][activityIdx].activity, activity, s_maxStringLength-1);
                    if (activityIdx < s_maxEntriesPerDay)
                        activityIdx++;
                    else
                        activityIdx = -1;

                    res = true;
                }
            }
        } 

        seekEOL = true;
    }

    if (!res) {
        *errStr = "No entries found (invalid format?)";
    }

    return res;
}

