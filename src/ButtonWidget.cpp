//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeMonoBold24pt7b.h"

#include "ButtonWidget.hpp"

void ButtonWidget::setWidth(int width) {
    m_width = width;
}

void ButtonWidget::setDisabled(bool disabled) {
    m_disabled = disabled;
}

void ButtonWidget::setText(const char* text) {
    if (text) {
        strncpy(m_text, text, 32);
    }
}

void ButtonWidget::setTextOffset(int offset) {
    m_textOffset = offset;
}

void ButtonWidget::setIcon(const unsigned char* icon) {
    m_icon = icon;
}

void ButtonWidget::setIconOffset(int offset) {
    m_iconOffset = offset;
}

void ButtonWidget::setIconWidth(int width) {
    m_iconWidth = width;
}

void ButtonWidget::setAction(ActionHandler action) {
    m_actionHandler = action;
}

int ButtonWidget::getWidth() {
    return m_width;
}

int ButtonWidget::getHeight() {
    return s_height;
}

bool ButtonWidget::render(Inkplate* context) {
    if (!m_disabled) {
        context->drawRoundRect(m_xpos, m_ypos, m_width, s_height, s_cornerRadius, BLACK);
        context->drawRoundRect(m_xpos+1, m_ypos+1, m_width-2, s_height-2, s_cornerRadius-1, BLACK);
        context->drawRoundRect(m_xpos+2, m_ypos+2, m_width-4, s_height-4, s_cornerRadius-2, BLACK);
        #if CONFIG_ADD_3D_EDGE
            context->drawRoundRect(m_xpos, m_ypos, m_width-4, s_height-4, s_cornerRadius-2, BLACK);
        #endif
    } else {
        context->drawRoundRect(m_xpos, m_ypos, m_width, s_height, s_cornerRadius, BLACK);
    }
    
    if (m_icon)
        context->drawBitmap(m_xpos+10+m_iconOffset, m_ypos+10, m_icon, m_iconWidth, s_iconHeight, WHITE, BLACK);

    if (m_text[0]) {
        const GFXfont* font = &FreeMonoBold24pt7b;
        context->setFont(font);
        context->setTextColor(BLACK);
        context->setCursor(m_xpos+25+m_textOffset, m_ypos + s_height/2 + 13);
        context->setTextSize(1);
        context->println(m_text);
    }
    return false;
}

bool ButtonWidget::touch(Inkplate* context) {
    if (m_disabled)
        return false;

    bool res = false;
    if (context->touchInArea(m_xpos, m_ypos, m_width, s_height)) {
        if (m_actionHandler)
            m_actionHandler();
        res = true;
    }
    return res;
}