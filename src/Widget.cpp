//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Widget.hpp"

int Widget::getXpos() {
    return m_xpos;
}

int Widget::getYpos() {
    return m_ypos;
}

void Widget::setXYpos(int xpos, int ypos) {
    m_xpos = xpos;
    m_ypos = ypos;
}

bool Widget::touch(Inkplate* context) {
    return false;
};