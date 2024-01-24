//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"

class Inkplate;

class Widget {
public:
    Widget() :
        m_xpos(0), m_ypos(0)
        {};
    ~Widget() {};

    int     getXpos();
    int     getYpos();
    void    setXYpos(int xpos, int ypos);

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;

    virtual bool render(Inkplate* context) = 0;
    virtual bool touch(Inkplate* context);

protected:
    int     m_xpos = 0;
    int     m_ypos = 0;
};