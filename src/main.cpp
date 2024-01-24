//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#ifndef ARDUINO_INKPLATE6PLUS
    #error "Wrong board selection for this example, please select Inkplate 6PLUS in the boards menu."
#endif

#include "Inkplate.h"

#include "config.hpp"
#include "Logger.hpp"
#include "SystemCore.hpp"
#include "EventManager.hpp"
#include "ViewController.hpp"
#include "ProfileManager.hpp"

#include "helper.hpp"

static SystemCore       g_systemCore;
static EventManager     g_eventManager;
static ProfileManager   g_profileManager;
static ViewController   g_viewController;

void setup() {
    g_systemCore.initSerial();
    g_systemCore.initInkplate();
    g_systemCore.initTouch();
    g_systemCore.initTimer();
    g_systemCore.initFS();
    g_systemCore.setEventDelegate(&g_eventManager);
    g_systemCore.loadSettings();
   
    g_eventManager.setSystemCoreDelegate(&g_systemCore);
    g_eventManager.setViewDelegate(&g_viewController);
    g_eventManager.setProfileDelegate(&g_profileManager);

    g_profileManager.setSystemCoreDelegate(&g_systemCore);
    g_profileManager.loadAllProfiles();

    g_viewController.setSystemCoreDelegate(&g_systemCore);
    g_viewController.setEventDelegate(&g_eventManager);
    g_viewController.setProfileDelegate(&g_profileManager);

    int width, height;
    g_systemCore.getDisplaySize(&width, &height);
    g_viewController.createViews(width, height);

    g_viewController.showMainView();
    g_systemCore.setCurrentView(g_viewController.getCurrentView());
    g_systemCore.doRender();
}

void loop() {
    g_systemCore.handleTouch();
    g_systemCore.handleTimer();

    delay(20);
}
