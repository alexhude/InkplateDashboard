//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"

class Inkplate;
class EventManagerDelegate;

class View {
public:
    View() {};
    ~View() {};

    void setEventDelegate(EventManagerDelegate* delegate);

public:

    virtual const char* getName() = 0;

    virtual void create(int width, int height) = 0;
	virtual bool render(Inkplate* context) = 0;
    virtual bool touch(Inkplate* context) = 0;

protected:

    EventManagerDelegate*   m_eventDelegate = nullptr;

};