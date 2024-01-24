//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "TokenTypes.hpp"
#include "config.hpp"

class View;
class Profile;
class ProfileFile;

class ProfileManagerDelegate {
public:
    virtual bool loadAllProfiles() = 0;
    virtual bool saveAllProfiles() = 0;
    virtual bool saveProfile(int profileIdx) = 0;
    virtual bool loadProfile(int profileIdx) = 0;
    virtual int getMaxProfilesNumber() = 0;

    virtual bool importProfile(int profileIdx, const char** errStr) = 0;
    virtual bool importActivityList(int profileIdx, const char** errStr) = 0;

    virtual bool isActive(int profileIdx) = 0;

    virtual void tickMinute() = 0;
    virtual void tickWeek() = 0;
    virtual void enableTimer(int profileIdx) = 0;
    virtual void disableTimer(int profileIdx) = 0;

    virtual const char* getName(int profileIdx) = 0;
    virtual int getTotalTime(int profileIdx) = 0;
    virtual const char* getTotalTimeString(int profileIdx) = 0;
    virtual void setTotalTime(int profileIdx, int time) = 0;
    virtual int getRemainTime(int profileIdx) = 0;
    virtual int getSessionTime(int profileIdx) = 0;
    virtual void addMinutes(int profileIdx, int minutes) = 0;
    virtual void removeMinutes(int profileIdx, int minutes) = 0;

    virtual bool tokenTypeRequested(int profileIdx, TokenType type) = 0;
    virtual void requestToken(int profileIdx, TokenType type) = 0;
    virtual void cancelTokenRequest(int profileIdx, TokenType type) = 0;
    virtual void approveTokenRequest(int profileIdx, TokenType type) = 0;
    virtual void covertTokenToMins(int profileIdx, int minutes) = 0;
    virtual int getTokens(int profileIdx) = 0;
    virtual const char* getTokensString(int profileIdx) = 0;

    virtual bool getActivity(int profileIdx, int actIdx, int* time, const char** text, int weekDay = -1) = 0;
    virtual void clearAllActivities(int profileIdx) = 0;

    virtual void factoryReset() = 0;

    virtual void dumpDiagnostics() = 0;
};