//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"
#include "ProfileManagerDelegate.hpp"
#include "Profile.hpp"

class SystemCoreDelegate;

class ProfileManager : public ProfileManagerDelegate {
public:
    ProfileManager() {};
    ~ProfileManager() {};

    void setSystemCoreDelegate(SystemCoreDelegate* delegate);

public: // ProfileManagerDelegate

    bool loadAllProfiles() override;
    bool saveAllProfiles() override;
    bool loadProfile(int profileIdx) override;
    bool saveProfile(int profileIdx) override;
    int getMaxProfilesNumber() override;

    bool importProfile(int profileIdx, const char** errStr) override;
    bool importActivityList(int profileIdx, const char** errStr) override;

    bool isActive(int profileIdx) override;

    void tickMinute() override;
    void tickWeek() override;
    void enableTimer(int profileIdx) override;
    void disableTimer(int profileIdx) override;

    const char* getName(int profileIdx) override;
    int getTotalTime(int profileIdx) override;
    const char* getTotalTimeString(int profileIdx) override;
    void setTotalTime(int profileIdx, int time) override;
    int getRemainTime(int profileIdx) override;
    int getSessionTime(int profileIdx) override;
    void addMinutes(int profileIdx, int minutes) override;
    void removeMinutes(int profileIdx, int minutes) override;

    bool tokenTypeRequested(int profileIdx, TokenType type) override;
    void requestToken(int profileIdx, TokenType type) override;
    void cancelTokenRequest(int profileIdx, TokenType type) override;
    void approveTokenRequest(int profileIdx, TokenType type) override;
    void covertTokenToMins(int profileIdx, int minutes) override;

    int getTokens(int profileIdx) override;
    const char* getTokensString(int profileIdx) override;

    bool getActivity(int profileIdx, int actIdx, int* time, const char** text, int weekDay = -1) override;
    void clearAllActivities(int profileIdx) override;

    void factoryReset() override;

    void dumpDiagnostics() override;

private:

    static const int s_maxProfileCount = 2;

    SystemCoreDelegate* m_systemCoreDelegate = nullptr;

    Profile m_profiles[s_maxProfileCount];

};