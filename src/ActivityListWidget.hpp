//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"
#include "Widget.hpp"

class Inkplate;
class Profile;

class ActivityListWidget : public Widget {
public:
    ActivityListWidget() {}
    ~ActivityListWidget() {};

    void setWidth(int width);
    void setHeight(int height);

    using TimeProvider = std::function<int()>;
    void setTimeProvider(TimeProvider fetchTime);

    using DataProvider = std::function<bool(int, int*, const char**)>;
    void setDataProvider(DataProvider fetchActivity);

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;

private:

    static const int s_maxEntryCount = 10;

    TimeProvider m_fetchTime = nullptr;
    DataProvider m_fetchActivity = nullptr;

    int          m_width = 100;
    int          m_height = 100;

};