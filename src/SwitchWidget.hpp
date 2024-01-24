//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include <functional>

#include "config.hpp"
#include "Widget.hpp"

class Inkplate;

class SwitchWidget : public Widget {
public:
    SwitchWidget() {}
    ~SwitchWidget() {};

    void setName(const char* name);

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

    static const int s_width = 520;
    static const int s_height = 60;

    static const unsigned char s_onImage[];
    static const unsigned char s_offImage[];

    ActionHandler  m_actionHandler = nullptr;

    const char*     m_switchName = nullptr;
    bool            m_isOn = false;

};