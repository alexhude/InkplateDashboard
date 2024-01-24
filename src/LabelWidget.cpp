//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "LabelWidget.hpp"

void LabelWidget::setFont(const GFXfont* font) {
    m_font = font;
}

void LabelWidget::setText(const char* text) {
    m_labelText = text;
}

int LabelWidget::getWidth() {
    return -1;
}

int LabelWidget::getHeight() {
    return -1;
}

bool LabelWidget::render(Inkplate* context) {
    if (m_font && m_labelText) {
        context->setFont(m_font);
        context->setTextColor(BLACK);
        context->setCursor(m_xpos, m_ypos);
        context->setTextSize(1);
        context->println(m_labelText);
    }
    return false;
}