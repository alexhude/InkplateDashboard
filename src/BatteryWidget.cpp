//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeMonoBold9pt7b.h"

#include "Profile.hpp"
#include "BatteryWidget.hpp"
#include "helper.hpp"

void BatteryWidget::showVoltage(bool enable) {
    m_showVoltage = enable;
}

void BatteryWidget::setDataProvider(BatteryPercentProvider fetchBatteryPercent, BatteryVoltageProvider fetchBatteryVoltage) {
    m_fetchBatteryPercent = fetchBatteryPercent;
    m_fetchBatteryVoltage = fetchBatteryVoltage;
}

int BatteryWidget::getWidth() {
    return s_width;
}

int BatteryWidget::getHeight() {
    return s_height;
}

bool BatteryWidget::render(Inkplate* context) {

    int levelWidth = 0;
    const int levelWidthMax = 25;

    int percent = 0;
    float voltage = 0.0;
    if (m_fetchBatteryPercent)
        percent = m_fetchBatteryPercent();

    if (m_fetchBatteryVoltage)
        voltage = m_fetchBatteryVoltage();

    if (!m_showVoltage) {
        const uint8_t icon[] PROGMEM = {
            0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0xff, 0xff, 0xfc, 0x80, 0x3f, 
            0xff, 0xff, 0xfc, 0x80, 0x3f, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 
            0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 
            0xfc, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x80, 0x3f, 0xff, 0xff, 0xfc, 
            0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x01, 0x80
        };
        
        levelWidth = (percent * levelWidthMax) / 100;

        context->drawBitmap(m_xpos, m_ypos, icon, 33, 15, WHITE, BLACK);
        context->drawThickLine(m_xpos + 3, m_ypos + 7, m_xpos + 3 + levelWidth, m_ypos + 7, BLACK, 8);
    } else {
        context->setFont(&FreeMonoBold9pt7b);
        context->setTextColor(BLACK);
        context->setCursor(m_xpos, m_ypos);
        context->setTextSize(1);

        char tmp[32] = {0};
        sprintf(tmp, "%.2fV", voltage);
        context->println(tmp);
    }

    return false;
}
