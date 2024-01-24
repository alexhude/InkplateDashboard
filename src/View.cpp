//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "View.hpp"
#include "helper.hpp"

void View::setEventDelegate(EventManagerDelegate* delegate) {
    m_eventDelegate = delegate;
}
