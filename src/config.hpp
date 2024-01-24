//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#define IP6P_HW_FRONTLIGHT_MIN 0
#define IP6P_HW_FRONTLIGHT_MAX 63

#define IP6P_HW_DISPLAY_W 1024
#define IP6P_HW_DISPLAY_H 768

#define CONFIG_VERBOSE_LOG 0
#define CONFIG_DEV_MODE_ON 0
#define CONFIG_ADD_3D_EDGE 1

#define MAX_FILE_SIZE_PROFILE       256
#define MAX_FILE_SIZE_ACTIVITY_LIST 2048

#define RTC_YEAR_BASE 2000

#define MAKE_VERSION(major, minor) (((major & 0xFF) << 8) | (minor & 0xFF))
#define FW_VERSION MAKE_VERSION(1, 0)