//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "stdint.h"

#include "TokenTypes.hpp"
#include "config.hpp"

static const int s_maxStringLength  = 32;
static const int s_maxEntriesPerDay = 10;
static const int s_maxTokenCount    = 99;

struct ProfileActivityEntry {
    bool        valid;
    int         time;
    char        activity[s_maxStringLength];
}; 

struct ProfileFileHeader {
    uint32_t            magic;
    uint32_t            size;
    uint32_t            version;
    uint32_t            crc;
};

struct ProfileFile {
    ProfileFileHeader       header;
    char                    name[s_maxStringLength];
    int                     totalTime;
    int                     remainTime;
    int                     tokens;
    bool                    tokenRequested[TokenType::Count];
    ProfileActivityEntry    activityList[7][10]; // 7 days a week, 10 entries per day
};

class Profile {
    
public:
    Profile() {};
    ~Profile() {};

    bool    isActive();

    char*   getName();
    int     getTotalTime();
    char*   getTotalTimeString();
    int     getRemainTime();
    int     getSessionTime();
    int     getTokens();
    char*   getTokensString();

    void    setName(char* name);
    void    setTotalTime(int minutes);
    void    setRemainTime(int minutes);
    void    addMinutes(int minutes);
    void    removeMinutes(int minutes);
    
    bool    tokenTypeRequested(TokenType type);
    void    requestToken(TokenType type);
    void    cancelTokenRequest(TokenType type);
    void    approveTokenRequest(TokenType type);
    void    covertTokenToMins(int minutes);

    bool    getActivity(int weekDay, int actIdx, int* time, const char** text);
    void    clearAllActivities();

    bool    isTimerActive();
    void    enableTimer();
    void    disableTimer();

    void    tickMinute();
    void    tickWeek();

    void    serializeData(void* data, int* bytes);
    bool    deserializeData(void* data, int bytes);

    bool    importProfile(char* data, int bytes, const char** errStr);
    bool    importActivityList(char* data, int bytes, const char** errStr);

private:

    bool    m_active = false;
    char    m_name[s_maxStringLength] = {0};
    int     m_totalTime = 0;
    char    m_totalTimeString[16] = {0};
    int     m_remainTime = 0;
    int     m_sessionTime = -1;
    int     m_tokens = 0;
    char    m_tokensString[16] = {0};
    bool    m_tokenRequested[TokenType::Count] = {false};

    bool    m_timerActive = false;
    
    ProfileActivityEntry    m_activityList[7][s_maxEntriesPerDay]; // 7 days a week, 10 entries per day
};