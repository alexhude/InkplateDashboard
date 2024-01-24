//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeMonoBold18pt7b.h"
#include "Fonts/FreeMonoBoldOblique12pt7b.h"

#include "Profile.hpp"
#include "RadialTimerWidget.hpp"

const int RadialTimerWidget::s_bitmask[] = {119, 48, 93, 121, 58, 107, 111, 49, 127, 59};
const int RadialTimerWidget::s_triangleX[] = {83, 101, 108, 101, 108, 277, 101, 108, 277, 257, 277, 108, 257, 277, 286, 76, 60, 98, 60, 98, 80, 80, 39, 60, 80, 39, 55, 31, 55, 73, 31, 73, 52, 31, 9, 52, 9, 52, 20, 61, 86, 80, 86, 80, 233, 233, 227, 80, 233, 227, 252, 260, 292, 305, 305, 260, 240, 305, 281, 240, 240, 281, 260, 259, 234, 276, 234, 276, 256, 256, 214, 234, 214, 256, 237, 38, 27, 60, 38, 60, 207, 207, 38, 212, 212, 207, 230};
const int RadialTimerWidget::s_triangleY[] = {30, 13, 60, 13, 60, 14, 13, 60, 14, 57, 14, 60, 57, 14, 29, 36, 47, 61, 47, 61, 198, 198, 201, 47, 198, 201, 219, 252, 232, 253, 252, 253, 390, 252, 406, 390, 406, 390, 416, 227, 202, 249, 202, 249, 203, 203, 247, 249, 203, 247, 224, 60, 35, 49, 49, 60, 200, 50, 201, 200, 200, 201, 220, 231, 252, 252, 252, 252, 403, 403, 390, 252, 390, 403, 415, 439, 424, 392, 439, 392, 394, 394, 439, 439, 439, 394, 424};

void RadialTimerWidget::setDataProvider(TotalTimeProvider fetchTotal, RemainTimeProvider fetchRemain, SessionTimeProvider fetchSession) {
    m_fetchTotal = fetchTotal;
    m_fetchRemain = fetchRemain;
    m_fetchSession = fetchSession;
}

int RadialTimerWidget::getWidth() {
    return s_size;
}

int RadialTimerWidget::getHeight() {
    return s_size;
}

bool RadialTimerWidget::render(Inkplate* context) {
    int totalTime = 0;
    int totalTimeReal = 0;
    int remainTime = 0;
    int sessionTime = -1;

    if (m_fetchTotal)
        totalTime = totalTimeReal = m_fetchTotal();

    if (m_fetchRemain)
        remainTime = m_fetchRemain();

    if (m_fetchSession)
        sessionTime = m_fetchSession();

    if (remainTime > totalTime)
        totalTime = remainTime;

    int h = remainTime / 60;
    int m = remainTime % 60;

    int center_x = m_xpos + (s_size/2);
    int center_y = m_ypos + (s_size/2);
    int digits_x = center_x - 75;
    int digits_y = center_y - 25;

    int rad_in = (double)s_size / 2 * 0.75;
    int rad_out = (double)s_size / 2 * 1.0;

    int sector;
    if (totalTime == 0)
        sector = -1;
    else
        sector = ((totalTime - remainTime) * 240) / totalTime;
    for (int i = 0; i < 240; ++i) {
        if (i < sector)
            continue;
        context->drawThickLine(
            center_x + rad_in * sin((double)i / 240.0 * 2.0 * PI),
            center_y - rad_in * cos((double)i / 240.0 * 2.0 * PI),
            center_x + rad_out * sin((double)i / 240.0 * 2.0 * PI),
            center_y - rad_out * cos((double)i / 240.0 * 2.0 * PI), 
            BLACK, 4);
    }

    char tmp[60] = {0};
    const GFXfont *font = nullptr;
    context->setTextColor(BLACK);
    context->setTextSize(1);

    if (sessionTime != -1) {
        sprintf(tmp, "%.2d:%.2d", sessionTime / 60, sessionTime % 60);
        context->setCursor(center_x - 52, center_y - 40);
        font = &FreeMonoBold18pt7b;
        context->setFont(font);
        context->print(tmp);
    }

    sprintf(tmp, "of %.2d:%.2d", totalTimeReal / 60, totalTimeReal % 60);
    context->setCursor(center_x - 55, center_y + 50);
    font = &FreeMonoBoldOblique12pt7b;
    context->setFont(font);
    context->print(tmp);

    context->drawCircle(center_x, center_y, rad_in-1, BLACK);
    context->drawCircle(center_x, center_y, rad_in-0, BLACK);
    context->drawCircle(center_x, center_y, rad_out+0, BLACK);
    context->drawCircle(center_x, center_y, rad_out+1, BLACK);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < sizeof(s_triangleX) / sizeof(s_triangleX[0]); j += 3) {
            int temp[4] = {h / 10 % 10, h % 10, m / 10 % 10, m % 10};
            int b = s_bitmask[temp[i]];
            if (b & (1 << ((j - 1) / (3 * 4)))) {
                context->fillTriangle(
                    (int)((float)i * (float)s_digitsMaxX / (float)s_digitsMaxY * (float)s_digitsSize * 1.1 + (float)digits_x + (float)s_digitsMaxX / (float)s_digitsMaxY * (float)s_digitsSize * (float)s_triangleX[j + 0] / (float)s_digitsMaxX),
                    (int)((float)digits_y + (float)s_digitsSize * (float)s_triangleY[j + 0] / (float)s_digitsMaxY),

                    (int)((float)i * (float)s_digitsMaxX / (float)s_digitsMaxY * (float)s_digitsSize * 1.1 + (float)digits_x + (float)s_digitsMaxX / (float)s_digitsMaxY * (float)s_digitsSize * (float)s_triangleX[j + 1] / (float)s_digitsMaxX),
                    (int)((float)digits_y + (float)s_digitsSize * (float)s_triangleY[j + 1] / (float)s_digitsMaxY),

                    (int)((float)i * (float)s_digitsMaxX / (float)s_digitsMaxY * (float)s_digitsSize * 1.1 + (float)digits_x + (float)s_digitsMaxX / (float)s_digitsMaxY * (float)s_digitsSize * (float)s_triangleX[j + 2] / (float)s_digitsMaxX),
                    (int)((float)digits_y + (float)s_digitsSize * (float)s_triangleY[j + 2] / (float)s_digitsMaxY),

                    BLACK);
            }
        }
    }

    int dot_rad = 0.05 * (float)s_digitsSize;

    context->fillCircle((int)((float)digits_x + 4.0 * (float)s_digitsMaxX / (float)s_digitsMaxY * (float)s_digitsSize * 1.090 / 2.0), (int)((float)digits_y + (float)s_digitsSize * 0.4), dot_rad, BLACK);
    context->fillCircle((int)((float)digits_x + 4.0 * (float)s_digitsMaxX / (float)s_digitsMaxY * (float)s_digitsSize * 1.075 / 2.0), (int)((float)digits_y + (float)s_digitsSize * 0.6), dot_rad, BLACK);
    return false;
}