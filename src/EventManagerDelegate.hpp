//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "TokenTypes.hpp"
#include "config.hpp"

class EventManagerDelegate {
public:
    // SystemCore
    virtual void tickMinute() = 0;
    virtual void tickWeek() = 0;

    // Profile
    virtual void timerStarted(int profileIdx) = 0;
    virtual void timerStopped(int profileIdx) = 0;

    // Auth Dialog
    virtual void authDialogShow() = 0;
    virtual void authDialogHide(char* pin) = 0;

    // Edit Dialog
    virtual void editDialogShow() = 0;
    virtual void editDialogHide(char* text) = 0;

    // Confirm Dialog
    virtual void confirmDialogShow() = 0;
    virtual void confirmDialogHide(bool ok) = 0;

    // OK Dialog
    virtual void okDialogShow() = 0;
    virtual void okDialogHide() = 0;

    // Menu
    virtual void menuScreenTimePressed() = 0;
    virtual void menuTokensPressed() = 0;
    virtual void menuTodoListPressed() = 0;
    virtual void menuSettingsPressed() = 0;
    virtual void menuBackToMainPressed() = 0;

    // Screentime
    virtual void screentimeAddMinutes(int profileIdx, int minutes) = 0;
    virtual void screentimeRemoveMinutes(int profileIdx, int minutes) = 0;
    virtual void screentimeSetTotalTime(int profileIdx, int time) = 0;

    // Tokens
    virtual void tokenRequest(int profileIdx, TokenType type) = 0;
    virtual void tokenCancelRequest(int profileIdx, TokenType type) = 0;
    virtual void tokenApproveRequest(int profileIdx, TokenType type) = 0;
    virtual void tokenConvertToMins(int profileIdx) = 0;

    // Settings
    virtual void settingsFrontlightEnabled(bool enabled) = 0;
    virtual void settingsFrontlightLevelChanged(int diff) = 0;
    virtual void settingsMinutesPerTokenChanged(int minutes) = 0;
    virtual void settingsDateChanged(const char* dateStr) = 0;  
    virtual void settingsTimeChanged(const char* timeStr) = 0;  
    virtual void settingsUpdatePIN(const char* pin) = 0;
    virtual void settingsFactoryReset() = 0;

    // Profile
    virtual bool profileSaveAll() = 0;
    virtual bool profileSaveData(int profileIdx) = 0;
    virtual bool profileLoadData(int profileIdx) = 0;
    virtual bool profileImportProfile(int profileIdx, const char** errStr) = 0;
    virtual bool profileImportActivityList(int profileIdx, const char** errStr) = 0;
    virtual void profileClearAllActivities(int profileIdx) = 0;

    // devmode
    virtual void dumpDiagnostics() = 0;
};