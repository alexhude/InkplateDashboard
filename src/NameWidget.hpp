//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include <functional>

#include "config.hpp"
#include "Widget.hpp"

class Inkplate;

class NameWidget : public Widget {
public:
    NameWidget() {}
    ~NameWidget() {};

    using NameProvider = std::function<const char*()>;
    void setDataProvider(NameProvider fetchName);

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;

private:

    NameProvider   m_fetchName = nullptr;
};