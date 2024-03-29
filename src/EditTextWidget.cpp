//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeMonoBold18pt7b.h"
#include "Fonts/FreeMonoBold24pt7b.h"

#include "EditTextWidget.hpp"
#include "helper.hpp"

const unsigned char EditTextWidget::s_backspaceIcon [] PROGMEM = {
    0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
    0x01, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xfe, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x80, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0xc0, 0x00, 0x03, 0x00, 0x00, 0x60, 0x00, 0x00, 0xff, 0x80, 0x00, 0x07, 0x80, 0x00, 
    0xf0, 0x00, 0x00, 0xff, 0x80, 0x00, 0x0f, 0xc0, 0x01, 0xf8, 0x00, 0x00, 0xff, 0x00, 0x00, 0x1f, 
    0xe0, 0x03, 0xfc, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x1f, 0xf0, 0x07, 0xfc, 0x00, 0x00, 0xfc, 0x00, 
    0x00, 0x0f, 0xf8, 0x0f, 0xf8, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x07, 0xfc, 0x1f, 0xf0, 0x00, 0x00, 
    0xf8, 0x00, 0x00, 0x03, 0xfe, 0x3f, 0xe0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x01, 0xff, 0x7f, 0xc0, 
    0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x7f, 
    0xff, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
    0x00, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 
    0x00, 0xc0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 
    0x80, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x01, 0xff, 0x7f, 0xc0, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x03, 
    0xfe, 0x3f, 0xe0, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x07, 0xfc, 0x1f, 0xf0, 0x00, 0x00, 0xfc, 0x00, 
    0x00, 0x0f, 0xf8, 0x0f, 0xf8, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x1f, 0xf0, 0x07, 0xfc, 0x00, 0x00, 
    0xff, 0x00, 0x00, 0x1f, 0xe0, 0x03, 0xfc, 0x00, 0x00, 0xff, 0x80, 0x00, 0x0f, 0xc0, 0x01, 0xf8, 
    0x00, 0x00, 0xff, 0xc0, 0x00, 0x07, 0x80, 0x00, 0xf0, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x03, 0x00, 
    0x00, 0x60, 0x00, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
    0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x80, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xff, 0xff, 0xe0, 0x00, 
    0x00, 0x00, 0x00, 0x07, 0x80
};

void EditTextWidget::setDataProvider(TextProvider fetchText) {
    m_fetchText = fetchText;
}

void EditTextWidget::setWidth(int width) {
    m_width = width;
}

void EditTextWidget::setHeight(int height) {
    m_height = height;
}

char* EditTextWidget::getText() {
    return m_text;
}

void EditTextWidget::setText(const char* text) {
    if (text) {
        strncpy(m_text, text, m_textLimit);
    }
}

void EditTextWidget::setTextLimit(int limit) {
    m_textLimit = limit;
}

void EditTextWidget::setTextOffset(int offset) {
    m_textOffset = offset;
}

void EditTextWidget::useSmallerFont(bool smallFont) {
    m_smallFont = smallFont;
}

void EditTextWidget::setSecureMode(bool secure) {
    m_secureMode = secure;
}

void EditTextWidget::hideDeleteButton(bool hide) {
    m_hideDeleteButton = hide;
}

int EditTextWidget::getWidth() {
    return m_width;
}

int EditTextWidget::getHeight() {
    return m_height;
}

void EditTextWidget::enterCharacter(char digit) {
    int len = strlen(m_text);
    if (len < m_textLimit) {
        m_text[len] = digit;
        m_text[len+1] = 0;
    }
}

void EditTextWidget::removeLastCharacter() {
    int len = strlen(m_text);
    if (len > 0)
        m_text[len-1] = 0;
}

bool EditTextWidget::render(Inkplate* context) {
    context->drawRoundRect(m_xpos, m_ypos, m_width, m_height, s_cornerRadius, BLACK);
    context->drawRoundRect(m_xpos+1, m_ypos+1, m_width-2, m_height-2, s_cornerRadius-1, BLACK);
    context->drawRoundRect(m_xpos+2, m_ypos+2, m_width-4, m_height-4, s_cornerRadius-2, BLACK);
    #if CONFIG_ADD_3D_EDGE
        context->drawRoundRect(m_xpos+3, m_ypos+3, m_width-4, m_height-4, s_cornerRadius-2, BLACK);
    #endif

    const char* text = nullptr;
    if (m_fetchText) {
        text = m_fetchText();
    } else if (m_text[0]) {
        text = m_text;
    }

    if (text) {
        if (m_smallFont)
            context->setFont(&FreeMonoBold18pt7b);
        else
            context->setFont(&FreeMonoBold24pt7b);
        context->setTextColor(BLACK);
        context->setCursor(m_xpos+20+m_textOffset, m_ypos + m_height/2 + 13);
        context->setTextSize(1);
        if (m_secureMode) {
            char tmp[16] = {0};
            char* cur = m_text;
            while (*cur) {
                tmp[cur-m_text] = '*';
                cur++;
            }
            context->println(tmp);
        } else {
            context->println(text);
        }
    }

    if (!m_hideDeleteButton) {
        context->drawBitmap(m_xpos+m_width-75, m_ypos+10, s_backspaceIcon, 65, 45, WHITE, BLACK);
    }
    return false;
}

bool EditTextWidget::touch(Inkplate* context) {
    if (!m_hideDeleteButton) {
        if (context->touchInArea(m_xpos+m_width-75, m_ypos+5, 55, 55)) {
            removeLastCharacter();
            return true;
        }
    }
    return false;
}
