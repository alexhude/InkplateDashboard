//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "TextWidget.hpp"
#include "helper.hpp"

void TextWidget::setFont(const GFXfont* font) {
    m_font = font;
}

void TextWidget::setText(const char* text) {
    m_text = text;
}

void TextWidget::setWidth(int width) {
    m_width = width;
}

void TextWidget::setTextAlignment(TextAlignment alignment) {
    m_alignment = alignment;
}

void TextWidget::setLineSpacing(int spacing) {
    m_lineSpacing = spacing;
}

int TextWidget::getWidth() {
    return m_width;
}

int TextWidget::getHeight() {
    return -1;
}

bool TextWidget::render(Inkplate* context) {
    if (m_font && m_text) {
        int xpos = m_xpos;
        int ypos = m_ypos;
        context->setFont(m_font);
        context->setTextColor(BLACK);
        context->setTextSize(1);

        int len = strlen(m_text);
        char* tmp = (char*)malloc(len+1);
        strncpy(tmp, m_text, len+1);
        tmp[len] = 0;

        const char* output = tmp;
        char* eos = strchr(output,'\n');
        if (!eos)
            eos = strchr(output,'\0');
        while (eos) {
            bool last = false;
            if (*eos == '\0')
                last = true;
                
            *eos = 0;

            int16_t x1, y1;
            uint16_t h, w;
            context->getTextBounds(output, 0, 0, &x1, &y1, &w, &h);

            if (m_alignment == TextAlignment::Left) {
                xpos = m_xpos;
            } else if (m_alignment == TextAlignment::Center) {
                xpos = m_xpos + ((m_width - w)/2);
            } else if (m_alignment == TextAlignment::Right) {
                xpos = m_xpos + (m_width - w);
            }

            context->setCursor(xpos, ypos);
            context->println(output);

            ypos += m_lineSpacing;

            if (last)
                break;

            output = eos + 1;
            eos = strchr(output,'\n');
            if (!eos)
                eos = strchr(output,'\0');
        }

        free(tmp);
    }
    return false;
}
