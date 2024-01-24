//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeSansBold18pt7b.h"

#include "TimerButtonWidget.hpp"
#include "helper.hpp"

void TimerButtonWidget::setAction(ActionHandler action) {
    m_actionHandler = action;
}

bool TimerButtonWidget::isOn() {
    return m_isOn;
}

void TimerButtonWidget::setOn() {
    m_isOn = true;
}

void TimerButtonWidget::setOff() {
    m_isOn = false;
}

int TimerButtonWidget::getWidth() {
    return s_size;
}

int TimerButtonWidget::getHeight() {
    return s_size;
}

bool TimerButtonWidget::render(Inkplate* context) {
    const GFXfont *font = &FreeSansBold18pt7b;

    context->drawRoundRect(m_xpos, m_ypos, s_size, s_size, s_cornerRadius, BLACK);
    context->drawRoundRect(m_xpos+1, m_ypos+1, s_size-2, s_size-2, s_cornerRadius-1, BLACK);
    context->drawRoundRect(m_xpos+2, m_ypos+2, s_size-4, s_size-4, s_cornerRadius-2, BLACK);
    #if CONFIG_ADD_3D_EDGE
        context->drawRoundRect(m_xpos, m_ypos, s_size-2, s_size-2, s_cornerRadius-1, BLACK);
        context->drawRoundRect(m_xpos, m_ypos, s_size-4, s_size-4, s_cornerRadius-2, BLACK);
    #endif
    context->setTextColor(BLACK);

    context->setFont(font);
    context->setTextSize(1);

    if (m_isOn) {
        context->setCursor(m_xpos + s_size/2 - 47, m_ypos + s_size/2 + 13);
        context->println("STOP");
    } else {
        context->setCursor(m_xpos + s_size/2 - 59, m_ypos + s_size/2 + 13);
        context->println("START");
    }
    return false;
}

bool TimerButtonWidget::touch(Inkplate* context) {
    if (context->touchInArea(m_xpos, m_ypos, s_size, s_size)) {
        m_isOn = !m_isOn;
        if (m_actionHandler)
            m_actionHandler(m_isOn);
        return true;
    }
    return false;
}