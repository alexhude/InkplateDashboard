//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"
#include "View.hpp"
#include "SeparatorWidget.hpp"
#include "LabelWidget.hpp"
#include "ButtonWidget.hpp"
#include "NameWidget.hpp"
#include "TimeWidget.hpp"
#include "EditTextWidget.hpp"
#include "NumberEditDialog.hpp"
#include "OKDialog.hpp"

class ProfileManagerDelegate;

class ScreenTimeView : public View {
public:
    ScreenTimeView() {};
    ~ScreenTimeView() {};

    void setProfileDelegate(ProfileManagerDelegate* delegate);

    bool showsDialog();
    void showEditDialog();
    void hideEditDialog(bool pass);
    void showOKDialog();
    void hideOKDialog();

public: // View

    const char* getName() override { return "ScreenTimeView"; }

    void create(int width, int height) override;
    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const int    m_maxProfileCount = 2;

    static const unsigned char s_backIcon[];
    static const unsigned char s_editIcon[];
    static const unsigned char s_importIcon[];

    ProfileManagerDelegate* m_profileDelegate = nullptr;

    SeparatorWidget     m_menuSplit { SeparatorType::RightOffset };
    SeparatorWidget     m_headerSplit { SeparatorType::TopOffset };
    SeparatorWidget     m_profileSplit { SeparatorType::VSplit };
    SeparatorWidget     m_timeSplit[m_maxProfileCount] = { 
        SeparatorType::BottomOffset,
        SeparatorType::BottomOffset
    };

    NameWidget          m_names[m_maxProfileCount];
    TimeWidget          m_remainTime[m_maxProfileCount];
    ButtonWidget        m_changeButtons[m_maxProfileCount][4];
    LabelWidget         m_changeLabels[m_maxProfileCount][2];
    LabelWidget         m_totalTimeLabel[m_maxProfileCount];
    EditTextWidget      m_totalTimeEdit[m_maxProfileCount];
    ButtonWidget        m_totalTimeButton[m_maxProfileCount];
    LabelWidget         m_importHeader[m_maxProfileCount];
    LabelWidget         m_importName[m_maxProfileCount];
    ButtonWidget        m_import[m_maxProfileCount];

    LabelWidget         m_menuName;
    ButtonWidget        m_menuBack;

    using EditHandler = std::function<void()>;
    NumberEditDialog    m_timeEditDialog;
    bool                m_showEditDialog = false;
    EditHandler         m_editPass = nullptr;
    EditHandler         m_editFail = nullptr;

    OKDialog            m_okDialog;
    bool                m_showOKDialog = false;

    bool                m_cacheView = false;

    char                m_importNameText[m_maxProfileCount][32] = { { 0 } };
};