//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "Inkplate.h"

#include "config.hpp"
#include "Widget.hpp"

class Inkplate;

class LabelWidget : public Widget {
public:
    LabelWidget() {}
    ~LabelWidget() {};

    void setFont(const GFXfont* font);
    void setText(const char* text);

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;

private:

    const GFXfont* m_font = nullptr;
    const char* m_labelText = nullptr;
};