//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include <functional>

#include "config.hpp"
#include "Widget.hpp"

class Inkplate;

class BatteryWidget : public Widget {
public:
    BatteryWidget() {}
    ~BatteryWidget() {};

    void showVoltage(bool enable);

    using BatteryPercentProvider = std::function<int()>;
    using BatteryVoltageProvider = std::function<float()>;
    void setDataProvider(BatteryPercentProvider fetchBatteryPercent, BatteryVoltageProvider fetchBatteryVoltage = nullptr);

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;

private:

    static const int s_width = 33;
    static const int s_height = 15;

    BatteryPercentProvider  m_fetchBatteryPercent = nullptr;
    BatteryVoltageProvider  m_fetchBatteryVoltage = nullptr;

    bool                    m_showVoltage = false;
};