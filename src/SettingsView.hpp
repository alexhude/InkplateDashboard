//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"
#include "View.hpp"
#include "SeparatorWidget.hpp"
#include "LabelWidget.hpp"
#include "SwitchWidget.hpp"
#include "EditTextWidget.hpp"
#include "TextWidget.hpp"
#include "ButtonWidget.hpp"
#include "BatteryWidget.hpp"
#include "NumberEditDialog.hpp"
#include "OKDialog.hpp"

class SystemCoreDelegate;

class SettingsView : public View {
public:
    SettingsView() {};
    ~SettingsView() {};

    void setSystemCoreDelegate(SystemCoreDelegate* delegate);

    bool showsDialog();
    void showAuthDialog();
    void hideAuthDialog(bool pass);
    void showEditDialog();
    void hideEditDialog(bool pass);
    void showOKDialog();
    void hideOKDialog();

public: // View

    const char* getName() override { return "SettingsView"; }

    void create(int width, int height) override;
    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const unsigned char s_backIcon[];
    static const unsigned char s_editIcon[];

    SystemCoreDelegate* m_systemCoreDelegate = nullptr;

    SeparatorWidget     m_menuSplit { SeparatorType::RightOffset };
    SeparatorWidget     m_headerSplit { SeparatorType::TopOffset };

    LabelWidget         m_menuName;
    ButtonWidget        m_menuBack;
    BatteryWidget       m_battery;

    LabelWidget         m_minsPerTokenLabel;
    EditTextWidget      m_minsPerTokenEdit;
    ButtonWidget        m_minsPerTokenButton;
    LabelWidget         m_dateLabel;
    EditTextWidget      m_dateEdit;
    ButtonWidget        m_dateButton;
    LabelWidget         m_timeLabel;
    EditTextWidget      m_timeEdit;
    ButtonWidget        m_timeButton;
    SwitchWidget        m_frontlight;
    ButtonWidget        m_frontlightPrev;
    EditTextWidget      m_frontlightPercent;
    ButtonWidget        m_frontlightNext;
    SwitchWidget        m_webserver;

    ButtonWidget        m_changePin;
    ButtonWidget        m_factoryReset;

    TextWidget          m_about;

    using AuthHandler = std::function<void()>;
    NumberEditDialog    m_authDialog;
    bool                m_showAuthDialog = false;
    AuthHandler         m_authPass = nullptr;
    AuthHandler         m_authFail = nullptr;

    using EditHandler = std::function<void()>;
    NumberEditDialog    m_editDialog;
    bool                m_showEditDialog = false;
    EditHandler         m_editPass = nullptr;
    EditHandler         m_editFail = nullptr;

    OKDialog            m_okDialog;
    bool                m_showOKDialog = false;

    bool                m_cacheView = false;

#if CONFIG_DEV_MODE_ON
    ButtonWidget        m_dumpDiag;
#endif
};