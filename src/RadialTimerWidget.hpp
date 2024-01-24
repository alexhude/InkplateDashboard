//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include <functional>

#include "config.hpp"
#include "Widget.hpp"

class Inkplate;

class RadialTimerWidget : public Widget {
public:
    RadialTimerWidget() {}
    ~RadialTimerWidget() {};

    using TotalTimeProvider = std::function<int()>;
    using RemainTimeProvider = std::function<int()>;
    using SessionTimeProvider = std::function<int()>;
    void setDataProvider(TotalTimeProvider fetchTotal, RemainTimeProvider fetchRemain, SessionTimeProvider fetchSession);

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;

private:

    static const int s_size = 250;
    static const int s_digitsSize = 50;
    static const int s_digitsMaxX = 310;
    static const int s_digitsMaxY = 440;

    static const int s_bitmask[];
    static const int s_triangleX[];
    static const int s_triangleY[];

    TotalTimeProvider m_fetchTotal = nullptr;
    RemainTimeProvider m_fetchRemain = nullptr;
    SessionTimeProvider m_fetchSession = nullptr;
};