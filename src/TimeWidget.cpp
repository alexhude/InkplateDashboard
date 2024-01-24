//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"

#include "TimeWidget.hpp"

const int TimeWidget::s_bitmask[] = {119, 48, 93, 121, 58, 107, 111, 49, 127, 59};
const int TimeWidget::s_triangleX[] = {83, 101, 108, 101, 108, 277, 101, 108, 277, 257, 277, 108, 257, 277, 286, 76, 60, 98, 60, 98, 80, 80, 39, 60, 80, 39, 55, 31, 55, 73, 31, 73, 52, 31, 9, 52, 9, 52, 20, 61, 86, 80, 86, 80, 233, 233, 227, 80, 233, 227, 252, 260, 292, 305, 305, 260, 240, 305, 281, 240, 240, 281, 260, 259, 234, 276, 234, 276, 256, 256, 214, 234, 214, 256, 237, 38, 27, 60, 38, 60, 207, 207, 38, 212, 212, 207, 230};
const int TimeWidget::s_triangleY[] = {30, 13, 60, 13, 60, 14, 13, 60, 14, 57, 14, 60, 57, 14, 29, 36, 47, 61, 47, 61, 198, 198, 201, 47, 198, 201, 219, 252, 232, 253, 252, 253, 390, 252, 406, 390, 406, 390, 416, 227, 202, 249, 202, 249, 203, 203, 247, 249, 203, 247, 224, 60, 35, 49, 49, 60, 200, 50, 201, 200, 200, 201, 220, 231, 252, 252, 252, 252, 403, 403, 390, 252, 390, 403, 415, 439, 424, 392, 439, 392, 394, 394, 439, 439, 439, 394, 424};

void TimeWidget::setDataProvider(TimeProvider fetchTime) {
    m_fetchTime = fetchTime;
}

void TimeWidget::setDigitSize(int digitSize) {
    m_digitsSize = digitSize;
}

int TimeWidget::getWidth() {
    return -1;
}

int TimeWidget::getHeight() {
    return -1;
}

bool TimeWidget::render(Inkplate* context) {
    int time = 0;

    if (m_fetchTime)
        time = m_fetchTime();

    int h = time / 60;
    int m = time % 60;

    int digits_x = m_xpos;
    int digits_y = m_ypos;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < sizeof(s_triangleX) / sizeof(s_triangleX[0]); j += 3) {
            int temp[4] = {h / 10 % 10, h % 10, m / 10 % 10, m % 10};
            int b = s_bitmask[temp[i]];
            if (b & (1 << ((j - 1) / (3 * 4)))) {
                context->fillTriangle(
                    (int)((float)i * (float)s_digitsMaxX / (float)s_digitsMaxY * (float)m_digitsSize * 1.1 + (float)digits_x + (float)s_digitsMaxX / (float)s_digitsMaxY * (float)m_digitsSize * (float)s_triangleX[j + 0] / (float)s_digitsMaxX),
                    (int)((float)digits_y + (float)m_digitsSize * (float)s_triangleY[j + 0] / (float)s_digitsMaxY),

                    (int)((float)i * (float)s_digitsMaxX / (float)s_digitsMaxY * (float)m_digitsSize * 1.1 + (float)digits_x + (float)s_digitsMaxX / (float)s_digitsMaxY * (float)m_digitsSize * (float)s_triangleX[j + 1] / (float)s_digitsMaxX),
                    (int)((float)digits_y + (float)m_digitsSize * (float)s_triangleY[j + 1] / (float)s_digitsMaxY),

                    (int)((float)i * (float)s_digitsMaxX / (float)s_digitsMaxY * (float)m_digitsSize * 1.1 + (float)digits_x + (float)s_digitsMaxX / (float)s_digitsMaxY * (float)m_digitsSize * (float)s_triangleX[j + 2] / (float)s_digitsMaxX),
                    (int)((float)digits_y + (float)m_digitsSize * (float)s_triangleY[j + 2] / (float)s_digitsMaxY),

                    BLACK);
            }
        }
    }

    int dot_rad = 0.05 * (float)m_digitsSize;

    context->fillCircle((int)((float)digits_x + 4.0 * (float)s_digitsMaxX / (float)s_digitsMaxY * (float)m_digitsSize * 1.090 / 2.0), (int)((float)digits_y + (float)m_digitsSize * 0.4), dot_rad, BLACK);
    context->fillCircle((int)((float)digits_x + 4.0 * (float)s_digitsMaxX / (float)s_digitsMaxY * (float)m_digitsSize * 1.075 / 2.0), (int)((float)digits_y + (float)m_digitsSize * 0.6), dot_rad, BLACK);

    return false;
}