//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include <functional>

#include "config.hpp"
#include "View.hpp"
#include "SeparatorWidget.hpp"
#include "NameWidget.hpp"
#include "RadialTimerWidget.hpp"
#include "TokenWidget.hpp"
#include "TimerButtonWidget.hpp"
#include "ActivityListWidget.hpp"
#include "ButtonWidget.hpp"
#include "TextWidget.hpp"
#include "TimeWidget.hpp"
#include "BatteryWidget.hpp"
#include "NumberEditDialog.hpp"
#include "Banner.hpp"

class SystemCoreDelegate;
class ProfileManagerDelegate;

class MainView : public View {
public:
    MainView() {};
    ~MainView() {};

    void setSystemCoreDelegate(SystemCoreDelegate* delegate);
    void setProfileDelegate(ProfileManagerDelegate* delegate);

    bool showsDialog();
    void showAuthDialog();
    void hideAuthDialog(bool pass);

public: // View

    const char* getName() override { return "MainView"; }

    void create(int width, int height) override;
    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const int    m_maxProfileCount = 2;

    static const unsigned char s_screenTimeIcon[];
    static const unsigned char s_tokensIcon[];
    static const unsigned char s_todoListIcon[];
    static const unsigned char s_settingsIcon[];

    SystemCoreDelegate* m_systemCoreDelegate = nullptr;
    ProfileManagerDelegate* m_profileDelegate = nullptr;

    SeparatorWidget         m_menuSplit { SeparatorType::RightOffset };
    SeparatorWidget         m_profileSplit { SeparatorType::HSplit };
    SeparatorWidget         m_listSplit[m_maxProfileCount] = { 
        SeparatorType::LeftOffset,
        SeparatorType::LeftOffset
    };

    NameWidget              m_names[m_maxProfileCount];
    RadialTimerWidget       m_radialTimers[m_maxProfileCount];
    TokenWidget             m_tokens[m_maxProfileCount];
    TimerButtonWidget       m_timerButtons[m_maxProfileCount];
    ActivityListWidget      m_activity[m_maxProfileCount];

    ButtonWidget            m_menuScreentime;
    ButtonWidget            m_menuTokens;
    ButtonWidget            m_menuTodoList;
    ButtonWidget            m_menuSettings;

    TimeWidget              m_time;
    BatteryWidget           m_battery;

    using AuthHandler = std::function<void()>;
    NumberEditDialog        m_authDialog;
    bool                    m_showAuthDialog = false;
    AuthHandler             m_authPass = nullptr;
    AuthHandler             m_authFail = nullptr;

    Banner                  m_errorBanner;
    bool                    m_showErrorBanner = false;

    bool                    m_cacheView = false;
};