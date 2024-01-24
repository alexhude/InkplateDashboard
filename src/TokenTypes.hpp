//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"

enum TokenType : int {
    HelpingParents,
    SelfEducation,
    CreativeProjects,
    Housekeeping,
    Miscellaneous,
    Count,
    Undefined = -1
};

static const char* TokenTypeString[TokenType::Count] __attribute__((__unused__)) = {
    "Helping Parents",
    "Self Education",
    "Creative Project",
    "Housekeeping",
    "Miscellaneous",
};