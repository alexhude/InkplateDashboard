//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "EventManager.hpp"
#include "SystemCoreDelegate.hpp"
#include "ViewControllerDelegate.hpp"
#include "ProfileManagerDelegate.hpp"

#include "helper.hpp"

void EventManager::setSystemCoreDelegate(SystemCoreDelegate* delegate) {
    m_systemCoreDelegate = delegate;
}

void EventManager::setViewDelegate(ViewControllerDelegate* delegate) {
    m_viewDelegate = delegate;
}

void EventManager::setProfileDelegate(ProfileManagerDelegate* delegate) {
    m_profileDelegate = delegate;
}

void EventManager::tickMinute() {
    vlog("EventManager::tickMinute");
    if (m_profileDelegate)
        m_profileDelegate->tickMinute();
}

void EventManager::tickWeek() {
    vlog("EventManager::tickWeek");
    if (m_profileDelegate)
        m_profileDelegate->tickWeek();
}

void EventManager::timerStarted(int profileIdx) {
    vlog("EventManager::timerStarted(%d)", profileIdx);
    if (m_profileDelegate)
        m_profileDelegate->enableTimer(profileIdx);
}

void EventManager::timerStopped(int profileIdx) {
    vlog("EventManager::timerStopped(%d)", profileIdx);
    if (m_profileDelegate) {
        m_profileDelegate->disableTimer(profileIdx);
        m_profileDelegate->saveProfile(profileIdx);
    }
}

void EventManager::authDialogShow() {
    vlog("EventManager::authDialogShow");
    if (m_viewDelegate)
        m_viewDelegate->showAuthDialog();
}

void EventManager::authDialogHide(char* pin) {
    vlog("EventManager::authDialogHide(%s)", (pin)? pin : "null");
    bool pass = false;
    if (pin) {
        if (m_systemCoreDelegate)
            pass = m_systemCoreDelegate->authPIN(pin);
    }
    if (m_viewDelegate)
        m_viewDelegate->hideAuthDialog(pass);
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->enableScreenCache(false);
    }
}

void EventManager::editDialogShow() {
    vlog("EventManager::editDialogShow");
    if (m_viewDelegate)
        m_viewDelegate->showEditDialog();
}

void EventManager::editDialogHide(char* text) {
    vlog("EventManager::editDialogHide(%s)", (text)? text : "null");
    bool pass = text != nullptr;
    if (m_viewDelegate)
        m_viewDelegate->hideEditDialog(pass);
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->enableScreenCache(false);
    }
}

void EventManager::confirmDialogShow() {
    vlog("EventManager::editDialogShow");
    if (m_viewDelegate)
        m_viewDelegate->showConfirmDialog();
}
void EventManager::confirmDialogHide(bool ok) {
    vlog("EventManager::confirmDialogHide(%d)", ok);
    if (m_viewDelegate)
        m_viewDelegate->hideConfirmDialog(ok);
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->enableScreenCache(false);
    }
}

void EventManager::okDialogShow() {
    vlog("EventManager::okDialogShow");
    if (m_viewDelegate)
        m_viewDelegate->showOKDialog();
}

void EventManager::okDialogHide() {
    vlog("EventManager::okDialogHide");
    if (m_viewDelegate)
        m_viewDelegate->hideOKDialog();
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->enableScreenCache(false);
    }
}

void EventManager::menuScreenTimePressed() {
    vlog("EventManager::menuScreenTimePressed");
    if (m_viewDelegate && m_systemCoreDelegate) {
        m_viewDelegate->showScreenTimeView();
        m_systemCoreDelegate->setCurrentView(m_viewDelegate->getCurrentView());
    }
}

void EventManager::menuTokensPressed() {
    vlog("EventManager::menuTokensPressed");
    if (m_viewDelegate && m_systemCoreDelegate) {
        m_viewDelegate->showTokensView();
        m_systemCoreDelegate->setCurrentView(m_viewDelegate->getCurrentView());
    }
}

void EventManager::menuTodoListPressed() {
    vlog("EventManager::menuTodoListPressed");
    if (m_viewDelegate && m_systemCoreDelegate) {
        m_viewDelegate->showActivityListView();
        m_systemCoreDelegate->setCurrentView(m_viewDelegate->getCurrentView());
    }
}

void EventManager::menuSettingsPressed() {
    vlog("EventManager::menuSettingsPressed");
    if (m_viewDelegate && m_systemCoreDelegate) {
        m_viewDelegate->showSettingsView();
        m_systemCoreDelegate->setCurrentView(m_viewDelegate->getCurrentView());
    }
}

void EventManager::menuBackToMainPressed() {
    vlog("EventManager::menuBackToMainPressed");
    if (m_viewDelegate && m_systemCoreDelegate) {
        m_viewDelegate->showMainView();
        m_systemCoreDelegate->setCurrentView(m_viewDelegate->getCurrentView());
    }
}

void EventManager::screentimeAddMinutes(int profileIdx, int minutes) {
    vlog("EventManager::screentimeAddMinutes(%d, %d)", profileIdx, minutes);
    if (m_profileDelegate) {
        m_profileDelegate->addMinutes(profileIdx, minutes);
        m_profileDelegate->saveProfile(profileIdx);
    }
}

void EventManager::screentimeRemoveMinutes(int profileIdx, int minutes) {
    vlog("EventManager::screentimeRemoveMinutes(%d, %d)", profileIdx, minutes);
    if (m_profileDelegate) {
        m_profileDelegate->removeMinutes(profileIdx, minutes);
        m_profileDelegate->saveProfile(profileIdx);
    }
}

void EventManager::screentimeSetTotalTime(int profileIdx, int time) {
    vlog("EventManager::screentimeSetTotalTime(%d)", profileIdx);
    if (m_profileDelegate) {
        m_profileDelegate->setTotalTime(profileIdx, time);
        m_profileDelegate->saveProfile(profileIdx);
    }
}

void EventManager::tokenRequest(int profileIdx, TokenType type) {
    vlog("EventManager::tokenRequest(%d, %d)", profileIdx, type);
    if (m_profileDelegate) {
        m_profileDelegate->requestToken(profileIdx, type);
        m_profileDelegate->saveProfile(profileIdx);
    }
}

void EventManager::tokenCancelRequest(int profileIdx, TokenType type) {
    vlog("EventManager::tokenCancelRequest(%d, %d)", profileIdx, type);
    if (m_profileDelegate) {
        m_profileDelegate->cancelTokenRequest(profileIdx, type);
        m_profileDelegate->saveProfile(profileIdx);
    }
}

void EventManager::tokenApproveRequest(int profileIdx, TokenType type) {
    vlog("EventManager::tokenApproveRequest(%d, %d)", profileIdx, type);
    if (m_profileDelegate) {
        m_profileDelegate->approveTokenRequest(profileIdx, type);
        m_profileDelegate->saveProfile(profileIdx);
    }
}

void EventManager::tokenConvertToMins(int profileIdx) {
    vlog("EventManager::tokenConvertToMins(%d)", profileIdx);
    if (m_profileDelegate) {
        if (m_systemCoreDelegate) {
            m_profileDelegate->covertTokenToMins(profileIdx, m_systemCoreDelegate->getMinsPerToken());
            m_profileDelegate->saveProfile(profileIdx);
        }
    }
}

void EventManager::settingsFrontlightEnabled(bool enabled) {
    vlog("EventManager::settingsFrontlightEnabled(%d)", enabled);
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->enableFrontlightLevel(enabled);
        m_systemCoreDelegate->saveSettings();
    }
}

void EventManager::settingsFrontlightLevelChanged(int diff) {
    vlog("EventManager::settingsFrontlightLevelChanged(%d)", diff);
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->setFrontlightLevel(m_systemCoreDelegate->getFrontlightLevel() + diff);
        m_systemCoreDelegate->saveSettings();
    }
}

void EventManager::settingsMinutesPerTokenChanged(int minutes) {
    vlog("EventManager::settingsMinutesPerTokenChanged(%d)", minutes);
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->setMinsPerToken(minutes);
        m_systemCoreDelegate->saveSettings();
    }
}

void EventManager::settingsDateChanged(const char* dateStr) {
    vlog("EventManager::settingsDateChanged(%s)", (dateStr)? dateStr : "null");
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->setDate(dateStr);
    }
}

void EventManager::settingsTimeChanged(const char* timeStr) {
    vlog("EventManager::settingsTimeChanged(%s)", (timeStr)? timeStr : "null");
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->setTime(timeStr);
    }
}

void EventManager::settingsUpdatePIN(const char* pin) {
    vlog("EventManager::settingsUpdatePIN(%s)", (pin)? pin : "null");
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->updatePIN(pin);
        m_systemCoreDelegate->saveSettings();
    }
}

void EventManager::settingsFactoryReset() {
    vlog("EventManager::settingsFactoryReset()");
    if (m_systemCoreDelegate) {
        m_systemCoreDelegate->factoryReset();
    }
    if (m_profileDelegate) {
        m_profileDelegate->factoryReset();
    }
}

bool EventManager::profileSaveAll() {
    vlog("EventManager::profileSaveAll");
    bool ret = false;
    if (m_profileDelegate)
        ret = m_profileDelegate->saveAllProfiles();
    return ret;
}

bool EventManager::profileSaveData(int profileIdx) {
    vlog("EventManager::profileSaveData(%d)", profileIdx);
    bool ret = false;
    if (m_profileDelegate) {
        ret = m_profileDelegate->saveProfile(profileIdx);
    }
    return ret;
}

bool EventManager::profileLoadData(int profileIdx) {
    vlog("EventManager::profileLoadData(%d)", profileIdx);
    bool ret = false;
    if (m_profileDelegate) {
        ret = m_profileDelegate->loadProfile(profileIdx);
    }
    return ret;
}

bool EventManager::profileImportProfile(int profileIdx, const char** errStr) {
    vlog("EventManager::profileImportProfile(%d)", profileIdx);
    bool ret = false;
    if (m_profileDelegate) {
        ret = m_profileDelegate->importProfile(profileIdx, errStr);
        if (ret) {
            m_profileDelegate->saveProfile(profileIdx);
        }
    }
    return ret;
}

bool EventManager::profileImportActivityList(int profileIdx, const char** errStr) {
    vlog("EventManager::profileImportActivityList(%d)", profileIdx);
    bool ret = false;
    if (m_profileDelegate) {
        ret = m_profileDelegate->importActivityList(profileIdx, errStr);
        if (ret) {
            m_profileDelegate->saveProfile(profileIdx);
        }
    }
    return ret;
}

void EventManager::profileClearAllActivities(int profileIdx) {
    vlog("EventManager::profileClearAllActivities(%d)", profileIdx);
    if (m_profileDelegate) {
        m_profileDelegate->clearAllActivities(profileIdx);
        m_profileDelegate->saveProfile(profileIdx);
    }
}

void EventManager::dumpDiagnostics() {
    if (m_systemCoreDelegate)
        m_systemCoreDelegate->dumpDiagnostics();
    if (m_viewDelegate)
        m_viewDelegate->dumpDiagnostics();
    if (m_profileDelegate)
        m_profileDelegate->dumpDiagnostics();
 }