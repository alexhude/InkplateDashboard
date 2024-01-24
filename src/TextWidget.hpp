//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "Inkplate.h"

#include "config.hpp"
#include "Widget.hpp"

enum class TextAlignment : int {
    Left,
    Center,
    Right,
};

class Inkplate;

class TextWidget : public Widget {
public:
    TextWidget() {}
    ~TextWidget() {};

    void setFont(const GFXfont* font);
    void setText(const char* text);
    void setWidth(int width);
    void setTextAlignment(TextAlignment alignment);
    void setLineSpacing(int spacing);

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;

private:

    const GFXfont*  m_font = nullptr;
    const char*     m_text = nullptr;
    int             m_width = 0;
    int             m_lineSpacing = 25;
    TextAlignment   m_alignment = TextAlignment::Left;

};