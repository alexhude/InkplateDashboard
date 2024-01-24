//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"

class View;
class Profile;

class SystemCoreDelegate {
public:
    virtual const char* getInitError() = 0;
    virtual void getDisplaySize(int* width, int* height) = 0;
    virtual void setCurrentView(View* view) = 0;
    virtual void forceFullClean(bool delay = false) = 0;
    virtual void enableScreenCache(bool enable) = 0;
    virtual bool loadSettings() = 0;
    virtual bool saveSettings() = 0;
    virtual bool frontlightEnabled() = 0;
    virtual int getFrontlightLevel() = 0;
    virtual const char* getFrontlightLevelString() = 0;
    virtual void enableFrontlightLevel(bool enable) = 0;
    virtual void setFrontlightLevel(int level) = 0;
    virtual int getMinsPerToken() = 0;
    virtual const char* getMinsPerTokenString() = 0;
    virtual void setMinsPerToken(int minutes) = 0;
    virtual bool authPIN(char* pin) = 0;
    virtual bool saveProfile(int index, void* data, int bytes) = 0;
    virtual bool loadProfile(int index, void* data, int* bytes) = 0;
    virtual bool importProfile(int index, void* data, int* bytes, const char** errStr) = 0;
    virtual bool importActivityList(int index, void* data, int* bytes, const char** errStr) = 0;
    virtual const char* getDateString() = 0;
    virtual const char* getTimeString() = 0;
    virtual int getMinutesForDay() = 0;
    virtual int getWeekDay() = 0;
    virtual int getBatteryPercent() = 0;
    virtual void setDate(const char* dateStr) = 0;
    virtual void setTime(const char* timeStr) = 0;
    virtual float getBatteryVoltage() = 0;
    virtual void updatePIN(const char* pin) = 0;
    virtual void factoryReset() = 0;

    virtual void dumpDiagnostics() = 0;
};