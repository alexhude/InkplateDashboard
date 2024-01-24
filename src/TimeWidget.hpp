//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include <functional>

#include "config.hpp"
#include "Widget.hpp"

class Inkplate;

class TimeWidget : public Widget {
public:
    TimeWidget() {}
    ~TimeWidget() {};

    using TimeProvider = std::function<int()>;
    void setDataProvider(TimeProvider fetchTime);

    void setDigitSize(int digitSize);

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;

private:

    static const int s_defaultDigitsSize = 50;
    static const int s_digitsMaxX = 310;
    static const int s_digitsMaxY = 440;

    static const int s_bitmask[];
    static const int s_triangleX[];
    static const int s_triangleY[];

    TimeProvider    m_fetchTime = nullptr;
    int             m_digitsSize = s_defaultDigitsSize;
};