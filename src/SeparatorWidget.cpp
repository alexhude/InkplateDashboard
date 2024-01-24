//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"

#include "SeparatorWidget.hpp"

void SeparatorWidget::setArea(int widht, int height) {
    m_width = widht;
    m_height = height;
}

void SeparatorWidget::setOffset(int offset) {
    m_offset = offset;
}

void SeparatorWidget::setLineWidth(int lineWidth) {
    m_lineWidth = lineWidth;
}

int SeparatorWidget::getLeftWidth() {
    switch (m_type) {
        case SeparatorType::VSplit: return m_width / 2;
        case SeparatorType::LeftOffset: return m_offset;
        case SeparatorType::RightOffset: return m_width - m_offset;
        default: return -1;
    }
    return -1;
}

int SeparatorWidget::getRightWidth() {
    switch (m_type) {
        case SeparatorType::VSplit: return m_width / 2;
        case SeparatorType::LeftOffset: return m_width - m_offset;
        case SeparatorType::RightOffset: return m_offset;
        default:
            return -1;
    }
}

int SeparatorWidget::getTopHeight() {
    switch (m_type)
    {
        case SeparatorType::HSplit: return m_height / 2;
        case SeparatorType::TopOffset: return m_offset;
        case SeparatorType::BottomOffset: return m_height - m_offset;
        default: return -1;
    }
    return -1;
}

int SeparatorWidget::getBottomHeight() {
    switch (m_type)
    {
        case SeparatorType::HSplit: return m_height / 2;
        case SeparatorType::TopOffset: return m_height - m_offset;
        case SeparatorType::BottomOffset: return m_offset;
        default: return -1;
    }
    return -1;
}

int SeparatorWidget::getWidth() {
    return m_width;
    switch (m_type) {
        case SeparatorType::HSplit:
        case SeparatorType::TopOffset:
        case SeparatorType::BottomOffset:
            return m_width;
        case SeparatorType::VSplit:
        case SeparatorType::LeftOffset:
        case SeparatorType::RightOffset:
            return m_lineWidth? m_lineWidth : 1;
        default: return - 1;
    }
    return -1;
}

int SeparatorWidget::getHeight() {
    return m_height;
    switch (m_type) {
        case SeparatorType::HSplit:
        case SeparatorType::TopOffset:
        case SeparatorType::BottomOffset:
            return m_lineWidth? m_lineWidth : 1;
        case SeparatorType::VSplit:
        case SeparatorType::LeftOffset:
        case SeparatorType::RightOffset:
            return m_height;
        default: return - 1;
    }
    return -1;
}

bool SeparatorWidget::render(Inkplate* context) {
    if (!context) return false;

    int x1, x2, y1, y2;

    switch (m_type)
    {
        case SeparatorType::HSplit: {
            y1 = y2 = m_height / 2;
            x1 = s_pad;
            x2 = m_width - s_pad;
            break;
        }
        case SeparatorType::VSplit: {
            x1 = x2 = m_width / 2;
            y1 = s_pad;
            y2 = m_height - s_pad;
            break;
        }
        case SeparatorType::LeftOffset: {
            x1 = x2 = m_offset;
            y1 = s_pad;
            y2 = m_height - s_pad;
            break;
        }
        case SeparatorType::RightOffset: {
            x1 = x2 = m_width - m_offset;
            y1 = s_pad;
            y2 = m_height - s_pad;
            break;
        }
        case SeparatorType::TopOffset: {
            y1 = y2 = m_offset;
            x1 = s_pad;
            x2 = m_width - s_pad;
            break;
        }
        case SeparatorType::BottomOffset: {
            y1 = y2 = m_height - m_offset;
            x1 = s_pad;
            x2 = m_width - s_pad;
            break;
        }
        default:
            return false;
    }

    x1 += m_xpos;
    x2 += m_xpos;

    y1 += m_ypos;
    y2 += m_ypos;

    if (m_lineWidth) {
        context->drawThickLine(x1, y1, x2, y2, BLACK, m_lineWidth);
    } else {
        context->drawLine(x1, y1, x2, y2, BLACK);
    }
    return false;
}