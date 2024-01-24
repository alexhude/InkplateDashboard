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
#include "TextWidget.hpp"
#include "ActivityListWidget.hpp"
#include "NumberEditDialog.hpp"
#include "OKDialog.hpp"

class SystemCoreDelegate;
class ProfileManagerDelegate;

class ActivityListView : public View {
public:
    ActivityListView() {};
    ~ActivityListView() {};

    void setProfileDelegate(ProfileManagerDelegate* delegate);

    bool showsDialog();
    void showAuthDialog();
    void hideAuthDialog(bool pass);
    void showOKDialog();
    void hideOKDialog();

public: // View

    const char* getName() override { return "ActivityListView"; }

    void create(int width, int height) override;
    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const int    m_maxProfileCount = 2;

    static const unsigned char s_backIcon[];
    static const unsigned char s_importIcon[];
    static const unsigned char s_clearIcon[];
    static const char* s_weekDays[7];

    ProfileManagerDelegate* m_profileDelegate = nullptr;

    SeparatorWidget     m_menuSplit { SeparatorType::RightOffset };
    SeparatorWidget     m_headerSplit { SeparatorType::TopOffset };
    SeparatorWidget     m_profileSplit { SeparatorType::VSplit };
    SeparatorWidget     m_activitySplit[m_maxProfileCount] = {
         SeparatorType::BottomOffset,
         SeparatorType::BottomOffset
    };

    NameWidget          m_names[m_maxProfileCount];

    ButtonWidget        m_prevDay[m_maxProfileCount];
    ButtonWidget        m_nextDay[m_maxProfileCount];
    TextWidget          m_weekDay[m_maxProfileCount];
    ActivityListWidget  m_activity[m_maxProfileCount];
    LabelWidget         m_importHeader[m_maxProfileCount];
    LabelWidget         m_importName[m_maxProfileCount];
    ButtonWidget        m_import[m_maxProfileCount];
    ButtonWidget        m_clear[m_maxProfileCount];

    LabelWidget         m_menuName;
    ButtonWidget        m_menuBack;

    using AuthHandler = std::function<void()>;
    NumberEditDialog    m_authDialog;
    bool                m_showAuthDialog = false;
    AuthHandler         m_authPass = nullptr;
    AuthHandler         m_authFail = nullptr;

    OKDialog            m_okDialog;
    bool                m_showOKDialog = false;

    bool                m_cacheView = false;

    char                m_importNameText[m_maxProfileCount][32] = { { 0 } };
    int                 m_weekDayIndex[m_maxProfileCount] = {
        1, 1
    };
};