//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "ViewController.hpp"
#include "SystemCoreDelegate.hpp"
#include "helper.hpp"

void ViewController::setSystemCoreDelegate(SystemCoreDelegate* delegate){
    m_systemCoreDelegate = delegate;
}

void ViewController::setEventDelegate(EventManagerDelegate* delegate) {
    m_eventDelegate = delegate;
}

void ViewController::setProfileDelegate(ProfileManagerDelegate* delegate) {
    m_profileDelegate = delegate;
}

void ViewController::createViews(int width, int height) {
    m_mainView.setSystemCoreDelegate(m_systemCoreDelegate);
    m_mainView.setEventDelegate(m_eventDelegate);
    m_mainView.setProfileDelegate(m_profileDelegate);
    m_mainView.create(width, height);
    
    m_settingsView.setSystemCoreDelegate(m_systemCoreDelegate);
    m_settingsView.setEventDelegate(m_eventDelegate);
    m_settingsView.create(width, height);
    
    m_screenTimeView.setEventDelegate(m_eventDelegate);
    m_screenTimeView.setProfileDelegate(m_profileDelegate);
    m_screenTimeView.create(width, height);
    
    m_tokensView.setEventDelegate(m_eventDelegate);
    m_tokensView.setProfileDelegate(m_profileDelegate);
    m_tokensView.create(width, height);

    m_activityListView.setEventDelegate(m_eventDelegate);
    m_activityListView.setProfileDelegate(m_profileDelegate);
    m_activityListView.create(width, height);
}

View* ViewController::getCurrentView() {
    return m_currentView;
}

void ViewController::showMainView() {
    m_currentView = &m_mainView;
}

void ViewController::showScreenTimeView() {
    m_currentView = &m_screenTimeView;
}

void ViewController::showTokensView() {
    m_currentView = &m_tokensView;
}

void ViewController::showActivityListView() {
    m_currentView = &m_activityListView;
}

void ViewController::showSettingsView() {
    m_currentView = &m_settingsView;
}

void ViewController::showAuthDialog() {
    if (m_currentView == &m_mainView) {
        m_mainView.showAuthDialog();
    } else if (m_currentView == &m_tokensView) {
        m_tokensView.showAuthDialog();
    } else if (m_currentView == &m_activityListView) {
        m_activityListView.showAuthDialog();
    } else if (m_currentView == &m_settingsView) {
        m_settingsView.showAuthDialog();
    }
}

void ViewController::hideAuthDialog(bool pass) {
    if (m_currentView == &m_mainView) {
        m_mainView.hideAuthDialog(pass);
    } else if (m_currentView == &m_tokensView) {
        m_tokensView.hideAuthDialog(pass);
    } else if (m_currentView == &m_activityListView) {
        m_activityListView.hideAuthDialog(pass);
    } else if (m_currentView == &m_settingsView) {
        m_settingsView.hideAuthDialog(pass);
    }
}

void ViewController::showEditDialog() {
    if (m_currentView == &m_screenTimeView) {
        m_screenTimeView.showEditDialog();
    } else if (m_currentView == &m_settingsView) {
        m_settingsView.showEditDialog();
    }
}

void ViewController::hideEditDialog(bool pass) {
    if (m_currentView == &m_screenTimeView) {
        m_screenTimeView.hideEditDialog(pass);
    } else if (m_currentView == &m_settingsView) {
        m_settingsView.hideEditDialog(pass);
    }
}

void ViewController::showConfirmDialog() {
    if (m_currentView == &m_tokensView) {
        m_tokensView.showConfirmDialog();
    }
}

void ViewController::hideConfirmDialog(bool pass) {
    if (m_currentView == &m_tokensView) {
        m_tokensView.hideConfirmDialog(pass);
    }
}

void ViewController::showOKDialog() {
    if (m_currentView == &m_screenTimeView) {
        m_screenTimeView.showOKDialog();
    } else if (m_currentView == &m_activityListView) {
        m_activityListView.showOKDialog();
    } else if (m_currentView == &m_settingsView) {
        m_settingsView.showOKDialog();
    }
}

void ViewController::hideOKDialog() {
    if (m_currentView == &m_screenTimeView) {
        m_screenTimeView.hideOKDialog();
    } else if (m_currentView == &m_activityListView) {
        m_activityListView.hideOKDialog();
    } else if (m_currentView == &m_settingsView) {
        m_settingsView.hideOKDialog();
    }
}

void ViewController::dumpDiagnostics() {
    dlog("ViewController:");
    dlog("  m_currentView = '%s'", (m_currentView)? m_currentView->getName() : "nullptr");
    dlog("  MainView::showsDialog = %d", m_mainView.showsDialog());
    dlog("  ScreenTimeView::showsDialog = %d", m_screenTimeView.showsDialog());
}