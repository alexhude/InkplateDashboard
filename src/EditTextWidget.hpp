//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

class Inkplate;

#include "config.hpp"
#include "Widget.hpp"
#include "ButtonWidget.hpp"

class Inkplate;

class EditTextWidget : public Widget {
public:
    EditTextWidget() {};
    ~EditTextWidget() {};

    using TextProvider = std::function<const char*()>;
    void setDataProvider(TextProvider fetchText);

    void setWidth(int width);
    void setHeight(int height);
    char* getText();
    void setText(const char* text);
    void setTextLimit(int limit);
    void setTextOffset(int offset);
    void useSmallerFont(bool smallFont);
    void setSecureMode(bool secure);
    void hideDeleteButton(bool hide);

    void enterCharacter(char digit);
    void removeLastCharacter();

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const int s_defaultHeight = 80;
    static const int s_cornerRadius = 8;
    static const unsigned char s_backspaceIcon[];

    TextProvider    m_fetchText = nullptr;

    ButtonWidget    m_delete;
    bool            m_hideDeleteButton = false;

    bool    m_secureMode = false;
    int     m_width = s_defaultHeight;
    int     m_height = s_defaultHeight;
    char    m_text[16] = {0};
    int     m_textLimit = 16;
    int     m_textOffset = 0;
    bool    m_smallFont = false;

};