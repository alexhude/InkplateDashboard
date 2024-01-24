//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include <functional>

#include "config.hpp"
#include "Widget.hpp"

class Inkplate;

class ButtonWidget : public Widget {
public:
    ButtonWidget() {}
    ~ButtonWidget() {};

    void setWidth(int width);
    void setDisabled(bool disabled);
    void setText(const char* text);
    void setTextOffset(int offset);
    void setIcon(const unsigned char* icon);
    void setIconOffset(int offset);
    void setIconWidth(int width);

    using ActionHandler = std::function<void()>;
    void setAction(ActionHandler action);

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const int s_height = 80;
    static const int s_cornerRadius = 8;
    static const int s_iconHeight = 60;

    ActionHandler           m_actionHandler = nullptr;
    int                     m_width = s_height;
    bool                    m_disabled = false;
    char                    m_text[32] = {0};
    int                     m_textOffset = 0;
    const unsigned char*    m_icon = nullptr;
    int                     m_iconOffset = 0;
    int                     m_iconWidth = s_iconHeight;
};