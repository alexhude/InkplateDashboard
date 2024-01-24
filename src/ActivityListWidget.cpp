//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeMonoBold12pt7b.h"
#include "Fonts/FreeSans12pt7b.h"
#include "Fonts/FreeSans18pt7b.h"

#include "ActivityListWidget.hpp"
#include "helper.hpp"

void ActivityListWidget::setWidth(int width) {
    m_width = width;
}

void ActivityListWidget::setHeight(int height) {
    m_height = height;
}

void ActivityListWidget::setTimeProvider(TimeProvider fetchTime) {
    m_fetchTime = fetchTime;
}

void ActivityListWidget::setDataProvider(DataProvider fetchActivity) {
    m_fetchActivity = fetchActivity; 
}

int ActivityListWidget::getWidth() {
    return m_width;
}

int ActivityListWidget::getHeight() {
    return -1;
}

bool ActivityListWidget::render(Inkplate* context) {

    if (!m_fetchActivity)
        return false;

    int ypos = m_ypos + 32;

    int minsNow = -1;
    if (m_fetchTime)
        minsNow = m_fetchTime();

    const GFXfont *font = nullptr;
    char tmp[64] = {0};
    int entryTime = 0;
    const char* entryText = nullptr;

    int16_t x1, y1;
    uint16_t h, w;

    context->setTextColor(BLACK);

    if (m_fetchActivity(0, &entryTime, &entryText)) {
        for (int i = 0; i < s_maxEntryCount; i++) {
            bool res = m_fetchActivity(i, &entryTime, &entryText);
            if (!res)
                continue;

            int xpos = m_xpos + 30;
            int xpos_cross = xpos - 10;

            sprintf(tmp, "%.2d:%.2d", entryTime / 60, entryTime % 60);

            font = &FreeMonoBold12pt7b;
            context->setFont(font);
            context->setTextSize(1);
            context->getTextBounds(tmp, 0, 0, &x1, &y1, &w, &h);
            context->setCursor(xpos, ypos + 15);
            context->print(tmp);

            int elen = strlen(entryText);
            strncpy(tmp, entryText, 64);
            
            xpos += w + 20;
            font = &FreeSans12pt7b;
            context->setFont(font);
            context->getTextBounds(entryText, 0, 0, &x1, &y1, &w, &h);
            while(w > (m_width - (xpos - m_xpos) - 30)) {
                tmp[elen] = '\0';
                tmp[elen-1] = '.';
                tmp[elen-2] = '.';
                tmp[elen-3] = '.';
                context->getTextBounds(tmp, 0, 0, &x1, &y1, &w, &h);
                elen--;
            }
            context->setCursor(xpos, ypos + 15);
            context->setTextSize(1);
            context->print(tmp);

            if (minsNow != -1) {
                if (minsNow >= entryTime) {
                    context->drawThickLine(xpos_cross, ypos + 9, xpos + w + 10, ypos + 9, BLACK, 2);
                }
            }

            ypos += 23 + 10;
            entryTime += 60;
        }
    } else {
        const char* text = "no activities";
        font = &FreeSans18pt7b;
        context->setFont(font);
        context->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
        context->setCursor(m_xpos + (m_width - w)/2, m_ypos + (m_height - h)/2 + h/2);
        context->setTextSize(1);
        context->print(text);
    }

    return false;
}
