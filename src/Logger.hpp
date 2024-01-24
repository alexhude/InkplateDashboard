//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"

class Logger {
public:
    static Logger* getInstance();

public:
    Logger();
    ~Logger() {};

    void enable();
    void disable();

    void log(const char* format, ...);

private:

    static Logger* s_instance;

    char s_logData[1024] = {0};
    bool m_enabled = false;
};