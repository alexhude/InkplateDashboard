//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Widget.hpp"

#pragma once

#include "config.hpp"

class Inkplate;

enum class SeparatorType : int {
    HSplit,
    VSplit,
    LeftOffset,
    RightOffset,
    TopOffset,
    BottomOffset,
    Undefined = -1
};

class SeparatorWidget : public Widget {
public:
    SeparatorWidget(SeparatorType type) 
        : m_type(type)
        {}
    ~SeparatorWidget() {};

    void setArea(int widht, int height);
    void setOffset(int offset);
    void setLineWidth(int lineWidth);

    int getLeftWidth();
    int getRightWidth();
    int getTopHeight();
    int getBottomHeight();

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;

private:

    static const int s_pad = 30;

    SeparatorType   m_type = SeparatorType::Undefined;
    int             m_offset = 0;
    int             m_width = 0;
    int             m_height = 0;

    int             m_lineWidth = 0;

};