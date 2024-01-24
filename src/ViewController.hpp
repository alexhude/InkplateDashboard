//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"
#include "ViewControllerDelegate.hpp"

#include "MainView.hpp"
#include "ScreenTimeView.hpp"
#include "TokensView.hpp"
#include "SettingsView.hpp"
#include "ActivityListView.hpp"

class SystemCoreDelegate;
class EventManagerDelegate;
class ProfileManagerDelegate;

class ViewController : public ViewControllerDelegate {
public:
    ViewController() {};
    ~ViewController() {};

    void setSystemCoreDelegate(SystemCoreDelegate* delegate);
    void setEventDelegate(EventManagerDelegate* delegate);
    void setProfileDelegate(ProfileManagerDelegate* delegate);

    void createViews(int width, int height);

public: // ViewControllerDelegate

    View* getCurrentView() override;
    void showMainView() override;
    void showScreenTimeView() override;
    void showTokensView() override;
    void showActivityListView() override;
    void showSettingsView() override;

    void showAuthDialog() override;
    void hideAuthDialog(bool pass) override;

    void showEditDialog() override;
    void hideEditDialog(bool pass) override;
    
    void showConfirmDialog() override;
    void hideConfirmDialog(bool pass) override;

    void showOKDialog() override;
    void hideOKDialog() override;

    void dumpDiagnostics() override;

private:

    SystemCoreDelegate* m_systemCoreDelegate = nullptr;
    EventManagerDelegate* m_eventDelegate = nullptr;
    ProfileManagerDelegate* m_profileDelegate = nullptr;

    View*           m_currentView;

    MainView        m_mainView;
    SettingsView    m_settingsView;
    ScreenTimeView  m_screenTimeView;
    TokensView      m_tokensView;
    ActivityListView    m_activityListView;
};