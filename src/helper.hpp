//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"
#include "Logger.hpp"

#define dlog(format, ...)										    \
	do {										                    \
		Logger* logger = Logger::getInstance();                     \
        if (logger) logger->log("[+] " format, ##__VA_ARGS__);	    \
	} while (0)

#define elog(format, ...)										    \
	do {										                    \
		Logger* logger = Logger::getInstance();                     \
        if (logger) logger->log("[!] " format, ##__VA_ARGS__);	    \
	} while (0)

#if CONFIG_VERBOSE_LOG
    #define vlog(format, ...)										    \
        do {										                    \
            Logger* logger = Logger::getInstance();                     \
            if (logger) logger->log("[*] " format, ##__VA_ARGS__);	    \
        } while (0)
#else
    #define vlog(format, ...)
#endif
