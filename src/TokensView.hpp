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
#include "TokenWidget.hpp"
#include "TokenTypes.hpp"
#include "TextWidget.hpp"
#include "NumberEditDialog.hpp"
#include "ConfirmDialog.hpp"

class ProfileManagerDelegate;

class TokensView : public View {
public:
    TokensView() {};
    ~TokensView() {};

    void setProfileDelegate(ProfileManagerDelegate* delegate);

    bool showsDialog();
    void showAuthDialog();
    void hideAuthDialog(bool pass);
    void showConfirmDialog();
    void hideConfirmDialog(bool pass);

public: // View

    const char* getName() override { return "TokensView"; }

    void create(int width, int height) override;
    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const int    m_maxProfileCount = 2;

    static const unsigned char s_backIcon[];
    static const unsigned char s_tokenParentHelpIcon[];
    static const unsigned char s_tokenEducationIcon[];
    static const unsigned char s_tokenCreativityIcon[];
    static const unsigned char s_tokenHousekeepingIcon[];
    static const unsigned char s_tokenMiscIcon[];
    static const unsigned char s_screenTimeIcon[];
    static const unsigned char s_moneyIcon[];
    static const unsigned char s_okIcon[];
    static const unsigned char s_cancelIcon[];

    ProfileManagerDelegate* m_profileDelegate = nullptr;

    SeparatorWidget     m_menuSplit { SeparatorType::RightOffset };
    SeparatorWidget     m_headerSplit { SeparatorType::TopOffset };
    SeparatorWidget     m_profileSplit { SeparatorType::VSplit };

    SeparatorWidget     m_requestSplit[m_maxProfileCount] = { 
        SeparatorType::BottomOffset, 
        SeparatorType::BottomOffset
    };
    NameWidget          m_names[m_maxProfileCount];
    TimeWidget          m_remainTime[m_maxProfileCount];
    ButtonWidget        m_requestButton[m_maxProfileCount][TokenType::Count];
    TextWidget          m_requestLabel[m_maxProfileCount][TokenType::Count];
    LabelWidget         m_pendingLabel[m_maxProfileCount][TokenType::Count];
    ButtonWidget        m_cancelButton[m_maxProfileCount][TokenType::Count];
    ButtonWidget        m_approveButton[m_maxProfileCount][TokenType::Count];

    TokenWidget         m_tokens[m_maxProfileCount];
    TextWidget          m_convertLabel[m_maxProfileCount];
    ButtonWidget        m_convertToTime[m_maxProfileCount];
    ButtonWidget        m_convertToMoney[m_maxProfileCount];

    LabelWidget         m_menuName;
    ButtonWidget        m_menuBack;

    char                m_requestLabelText[TokenType::Count][64] = { { 0 } };

    using AuthHandler = std::function<void()>;
    NumberEditDialog        m_authDialog;
    bool                    m_showAuthDialog = false;
    AuthHandler             m_authPass = nullptr;
    AuthHandler             m_authFail = nullptr;

    using ConfirmHandler = std::function<void()>;
    ConfirmDialog           m_confirmDialog;
    bool                    m_showConfirmDialog = false;
    AuthHandler             m_confirmPass = nullptr;
    AuthHandler             m_confirmFail = nullptr;

    bool                    m_cacheView = false;
};