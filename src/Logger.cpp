//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "stdio.h"
#include "stdarg.h"
#include "Inkplate.h"

#include "Logger.hpp"

Logger* Logger::s_instance = nullptr;

Logger* Logger::getInstance() {
    if(s_instance == nullptr){
        s_instance = new Logger();
    }
    return s_instance;
}

Logger::Logger() {
    if (!s_instance)
        s_instance = this;
}

void Logger::enable() {
    m_enabled = true;
    Serial.println("[+] logger enabled");
}

void Logger::disable() {
    m_enabled = false;
    Serial.println("[+] logger disabled");
}

void Logger::log(const char* format, ...) {
    if (!m_enabled) return;

    va_list arg;
    va_start(arg, format);
    vsnprintf(s_logData, 1024, format, arg);
    va_end(arg);

    Serial.println(s_logData);
}
