//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include <functional>

#include "config.hpp"
#include "Widget.hpp"

class Inkplate;

class TimerButtonWidget : public Widget {
public:
    TimerButtonWidget() {}
    ~TimerButtonWidget() {};

    using ActionHandler = std::function<void(bool)>;
    void setAction(ActionHandler action);

    bool isOn();
    void setOn();
    void setOff();

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const int s_size = 150;
    static const int s_cornerRadius = 15;

    ActionHandler  m_actionHandler = nullptr;

    bool m_isOn = false;

};