//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeMonoBoldOblique24pt7b.h"

#include "TokenWidget.hpp"

void TokenWidget::setDataProvider(TokenProvider fetchTokensString) {
    m_fetchTokensString = fetchTokensString;
}

int TokenWidget::getWidth() {
    return -1;
}

int TokenWidget::getHeight() {
    return -1;
}

bool TokenWidget::render(Inkplate* context) {
    const char* tokensText = "0"; 
    if (m_fetchTokensString)
        tokensText = m_fetchTokensString();

    const uint8_t icon[] PROGMEM = {
        0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xff, 0xe0, 0x3c, 0x07, 0xff, 0xff, 
        0xc3, 0xff, 0xc3, 0xff, 0xff, 0x0f, 0xff, 0xf0, 0xff, 0xfe, 0x1f, 0x81, 0xf8, 0x7f, 0xfc, 0x7c, 
        0x00, 0x3e, 0x3f, 0xfc, 0x78, 0x18, 0x1e, 0x3f, 0xf8, 0xe1, 0xff, 0x87, 0x1f, 0xf9, 0xc3, 0xff, 
        0xc3, 0x9f, 0xf1, 0xc7, 0xe7, 0xe3, 0x8f, 0xf3, 0x8f, 0xc3, 0xf1, 0xcf, 0xe3, 0x9f, 0xc3, 0xf9, 
        0xc7, 0xe7, 0x1f, 0x81, 0xf8, 0xe7, 0xe7, 0x3c, 0x18, 0x3c, 0xe7, 0xe7, 0x38, 0x3c, 0x1c, 0xe7, 
        0xe7, 0x38, 0xff, 0x1c, 0xe7, 0xc7, 0x3c, 0x7e, 0x3c, 0xe3, 0xe7, 0x3e, 0x3c, 0x7c, 0xe7, 0xe7, 
        0x3e, 0x3c, 0x7c, 0xe7, 0xe7, 0x3e, 0x20, 0x7c, 0xe7, 0xe7, 0x1e, 0x00, 0x78, 0xe7, 0xe3, 0x9e, 
        0x00, 0x79, 0xc7, 0xf3, 0x8f, 0x7e, 0xf1, 0xcf, 0xf1, 0xc7, 0xff, 0xe3, 0x8f, 0xf1, 0xc3, 0xff, 
        0xc3, 0x8f, 0xf8, 0xe1, 0xff, 0x87, 0x1f, 0xf0, 0x70, 0x3c, 0x0e, 0x0f, 0xe0, 0x3c, 0x00, 0x3c, 
        0x07, 0xc6, 0x1f, 0x81, 0xf8, 0x63, 0x8f, 0x0f, 0xff, 0xf0, 0xf1, 0x0f, 0xc3, 0xff, 0xc3, 0xf0, 
        0x01, 0xe0, 0x3c, 0x07, 0x80, 0xe0, 0xf0, 0x00, 0x0f, 0x07, 0xfc, 0xe3, 0x00, 0xc7, 0x3f, 0xfc, 
        0xc7, 0xff, 0xe3, 0x3f, 0xfc, 0x0f, 0xff, 0xf0, 0x3f, 0xfe, 0x1f, 0xff, 0xf8, 0x7f, 0xfe, 0x3f, 
        0xff, 0xfc, 0x7f, 0xfe, 0x7f, 0xff, 0xfe, 0x7f
    };
    
    context->drawBitmap(m_xpos, m_ypos, icon, 40, 40, WHITE, BLACK);

    const GFXfont *font = &FreeMonoBoldOblique24pt7b;
    context->setCursor(m_xpos+60, m_ypos+35);
    context->setFont(font);
    context->setTextColor(BLACK);
    context->setTextSize(1);
    context->print(tokensText);
    return false;
}
