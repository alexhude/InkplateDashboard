//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"
#include "EventManagerDelegate.hpp"

class SystemCoreDelegate;
class ViewControllerDelegate;
class ProfileManagerDelegate;

class EventManager : public EventManagerDelegate {
public:
    EventManager() {}
    ~EventManager() {};

    void setSystemCoreDelegate(SystemCoreDelegate* delegate);
    void setViewDelegate(ViewControllerDelegate* delegate);
    void setProfileDelegate(ProfileManagerDelegate* delegate);

public: // EventManagerDelegate

    // SystemCore
    void tickMinute() override;
    void tickWeek() override;

    // Profile View
    void timerStarted(int profileIdx) override;
    void timerStopped(int profileIdx) override;

    // Auth Dialog
    void authDialogShow() override;
    void authDialogHide(char* pin) override;

    // Edit Dialog
    void editDialogShow() override;
    void editDialogHide(char* text) override;

    // Confirm Dialog
    void confirmDialogShow() override;
    void confirmDialogHide(bool ok) override;

    // OK Dialog
    void okDialogShow() override;
    void okDialogHide() override;

    // Main Menu
    void menuScreenTimePressed() override;
    void menuTokensPressed() override;
    void menuTodoListPressed() override;
    void menuSettingsPressed() override;
    void menuBackToMainPressed() override;

    // Screentime
    void screentimeAddMinutes(int profileIdx, int minutes) override;
    void screentimeRemoveMinutes(int profileIdx, int minutes) override;
    void screentimeSetTotalTime(int profileIdx, int time) override;

    // Tokens
    void tokenRequest(int profileIdx, TokenType type) override;
    void tokenCancelRequest(int profileIdx, TokenType type) override;
    void tokenApproveRequest(int profileIdx, TokenType type) override;
    void tokenConvertToMins(int profileIdx) override;

    // Settings
    void settingsFrontlightEnabled(bool enabled) override;
    void settingsFrontlightLevelChanged(int diff) override;
    void settingsMinutesPerTokenChanged(int minutes) override;
    void settingsDateChanged(const char* dateStr) override;  
    void settingsTimeChanged(const char* timeStr) override;  
    void settingsUpdatePIN(const char* pin) override;
    void settingsFactoryReset() override;

    bool profileSaveAll() override;
    bool profileSaveData(int profileIdx) override;
    bool profileLoadData(int profileIdx) override;
    bool profileImportProfile(int profileIdx, const char** errStr) override;
    bool profileImportActivityList(int profileIdx, const char** errStr) override;
    void profileClearAllActivities(int profileIdx) override;

    // devmode
    void dumpDiagnostics() override;

private:

    SystemCoreDelegate*     m_systemCoreDelegate = nullptr;
    ViewControllerDelegate* m_viewDelegate = nullptr;
    ProfileManagerDelegate* m_profileDelegate = nullptr;

};