//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeSerifBoldItalic24pt7b.h"

#include "NameWidget.hpp"

void NameWidget::setDataProvider(NameProvider fetchName) {
    m_fetchName = fetchName;
}

int NameWidget::getWidth() {
    return -1;
}

int NameWidget::getHeight() {
    return -1;
}

bool NameWidget::render(Inkplate* context) {
    if (m_fetchName == nullptr) return false;

    const char* name = m_fetchName();

    const GFXfont *font = &FreeSerifBoldItalic24pt7b;
    context->setFont(font);
    context->setTextColor(BLACK);
    context->setCursor(m_xpos, m_ypos);
    context->setTextSize(1);
    context->println(name);
    return false;
}