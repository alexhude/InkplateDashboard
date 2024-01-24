//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeSansBoldOblique24pt7b.h"
#include "Fonts/FreeSerifBoldItalic24pt7b.h"
#include "Fonts/FreeSansBold12pt7b.h"
#include "Fonts/FreeSans12pt7b.h"

#include "SystemCoreDelegate.hpp"
#include "EventManagerDelegate.hpp"
#include "SettingsView.hpp"

#include "helper.hpp"

const unsigned char SettingsView::s_backIcon [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xfc, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xf0, 
	0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 
	0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 
	0xfe, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x00, 0x70, 0xff, 0x00, 0x03, 0xff, 0xff, 0xf8, 0x00, 0x30, 
	0xff, 0xc0, 0x03, 0xff, 0xff, 0xfe, 0x00, 0x30, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0x00, 0x30, 
	0xff, 0xf8, 0x03, 0xff, 0xff, 0xff, 0x00, 0x30, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xff, 0x80, 0x30, 
	0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x80, 0x30, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0x00, 0x30, 
	0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0x00, 0x30, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x30, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x30, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x70, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x70, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x70, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x01, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x07, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x7f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0
};

const unsigned char SettingsView::s_editIcon [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x3f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x1f, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x0f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x07, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x03, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xef, 0xc0, 0x01, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xe0, 0x01, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0x83, 0xf0, 0x03, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x01, 0xf8, 0x07, 0xf0, 
	0xff, 0xff, 0xff, 0xfe, 0x00, 0xfc, 0x0f, 0xf0, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7e, 0x1f, 0xf0, 
	0xff, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0x3f, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x1f, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x00, 0x00, 0x07, 0xff, 0xf0, 
	0xff, 0xff, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xf0, 
	0xff, 0xff, 0xf8, 0x00, 0x00, 0x3f, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xf0, 
	0xff, 0xff, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xc0, 0x00, 0x01, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 
	0xff, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 
	0xff, 0xf8, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xf0, 
	0xff, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xc0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 0xf0, 0xff, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 
	0xfe, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf0, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf0, 
	0xf8, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xf0, 
	0xf0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xf0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xf0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0
};

void SettingsView::setSystemCoreDelegate(SystemCoreDelegate* delegate) {
    m_systemCoreDelegate = delegate;
}

bool SettingsView::showsDialog() {
    return m_showAuthDialog || m_showEditDialog || m_showOKDialog;
}

void SettingsView::showAuthDialog() {
    m_authDialog.reset();
    m_showAuthDialog = true;
    m_cacheView = true;
}

void SettingsView::hideAuthDialog(bool pass) {
    m_showAuthDialog = false;
    if (pass)
        m_authPass();
    else
        m_authFail();
}

void SettingsView::showEditDialog() {
    m_editDialog.reset();
    m_showEditDialog = true;
    m_cacheView = true;
}

void SettingsView::hideEditDialog(bool pass) {
    m_showEditDialog = false;
    if (pass)
        m_editPass();
    else
        m_editFail();
}

void SettingsView::showOKDialog() {
    m_showOKDialog = true;
    m_cacheView = true;
}

void SettingsView::hideOKDialog() {
    m_showOKDialog = false;
}

void SettingsView::create(int width, int height) {
    m_menuSplit.setXYpos(0, 0);
    m_menuSplit.setArea(width, height);
    m_menuSplit.setOffset(100);

    m_headerSplit.setXYpos(0, 0);
    m_headerSplit.setArea(m_menuSplit.getLeftWidth(), height);
    m_headerSplit.setOffset(80);

    m_menuBack.setXYpos(m_menuSplit.getLeftWidth() + 10, 30);
    m_menuBack.setIcon(s_backIcon);
    m_menuBack.setAction([this] () {
        if (m_eventDelegate)
            m_eventDelegate->menuBackToMainPressed();
    });

    m_battery.setXYpos(m_menuSplit.getXpos() + m_menuSplit.getLeftWidth() + 22, height - 30);
    m_battery.setDataProvider([this] () -> int {
        if (m_systemCoreDelegate)
            return m_systemCoreDelegate->getBatteryPercent();
        return 0;
    }, [this] () -> float {
        if (m_systemCoreDelegate)
            return m_systemCoreDelegate->getBatteryVoltage();
        return 0;
    });
    m_battery.showVoltage(true);

    m_menuName.setXYpos(m_headerSplit.getXpos()+30, m_headerSplit.getYpos() + 60);
    m_menuName.setFont(&FreeSansBoldOblique24pt7b);
    m_menuName.setText("Settings");

    m_minsPerTokenLabel.setXYpos(m_headerSplit.getXpos() + 60, m_headerSplit.getTopHeight() + 40);
    m_minsPerTokenLabel.setFont(&FreeSansBold12pt7b);
    m_minsPerTokenLabel.setText("Minutes per token");

    m_minsPerTokenEdit.setXYpos(m_headerSplit.getXpos() + 60, m_headerSplit.getTopHeight() + 60);
    m_minsPerTokenEdit.setWidth(370);
    m_minsPerTokenEdit.setTextLimit(3);
    m_minsPerTokenEdit.hideDeleteButton(true);
    m_minsPerTokenEdit.setDataProvider([this] () -> const char* {
        if (m_systemCoreDelegate)
            return m_systemCoreDelegate->getMinsPerTokenString();
        return nullptr;
    });

    m_minsPerTokenButton.setXYpos(m_headerSplit.getXpos() + 60 + 520 - 80, m_headerSplit.getTopHeight() + 60);
    m_minsPerTokenButton.setIcon(s_editIcon);
    m_minsPerTokenButton.setAction([this] () {
        if (m_eventDelegate) {
            m_authPass = [this] () {
                m_editPass = [this] () {
					if (m_eventDelegate) {
						char* minutesStr = m_editDialog.getText();
						int minutes = atoi(minutesStr);
						m_eventDelegate->settingsMinutesPerTokenChanged(minutes);
					}
                };
                m_editFail = [this] () {
                };
                m_editDialog.setHeaderText("Enter minutes");
                m_editDialog.setTextLimit(3);
                m_eventDelegate->editDialogShow();
            };
            m_authFail = [this] () {
            };
            m_eventDelegate->authDialogShow();
        }
    });

    m_dateLabel.setXYpos(m_headerSplit.getXpos() + 60, m_minsPerTokenEdit.getYpos() + m_minsPerTokenEdit.getHeight() + 40);
    m_dateLabel.setFont(&FreeSansBold12pt7b);
    m_dateLabel.setText("Set Date (WDDMMYY)");

    m_dateEdit.setXYpos(m_headerSplit.getXpos() + 60, m_minsPerTokenEdit.getYpos() + m_minsPerTokenEdit.getHeight() + 60);
    m_dateEdit.setWidth(370);
    m_dateEdit.useSmallerFont(true);
    m_dateEdit.hideDeleteButton(true);
    m_dateEdit.setDataProvider([this] () -> const char* {
        if (m_systemCoreDelegate)
            return m_systemCoreDelegate->getDateString();
        return nullptr;
    });

    m_dateButton.setXYpos(m_headerSplit.getXpos() + 60 + 520 - 80, m_minsPerTokenEdit.getYpos() + m_minsPerTokenEdit.getHeight() + 60);
    m_dateButton.setIcon(s_editIcon);
    m_dateButton.setAction([this] () {
        if (m_eventDelegate) {
            m_authPass = [this] () {
                m_editPass = [this] () {
					if (m_eventDelegate) {
						const char* dateStr = m_editDialog.getText();
                        int dateLen = strlen(dateStr);
                        if (dateLen == 7) {
                            m_eventDelegate->settingsDateChanged(dateStr);
                        }
					}
                };
                m_editFail = [this] () {
                };
                m_editDialog.setHeaderText("Enter date");
                m_editDialog.setTextLimit(7);
                m_eventDelegate->editDialogShow();
            };
            m_authFail = [this] () {
            };
            m_eventDelegate->authDialogShow();
        }
    });

    m_timeLabel.setXYpos(m_dateButton.getXpos() + m_dateButton.getWidth() + 30, m_minsPerTokenEdit.getYpos() + m_minsPerTokenEdit.getHeight() + 40);
    m_timeLabel.setFont(&FreeSansBold12pt7b);
    m_timeLabel.setText("Set Time (HHMM)");

    m_timeEdit.setXYpos(m_dateButton.getXpos() + m_dateButton.getWidth() + 30, m_minsPerTokenEdit.getYpos() + m_minsPerTokenEdit.getHeight() + 60);
    m_timeEdit.setWidth(m_menuSplit.getLeftWidth() - 30 - 80 - m_timeEdit.getXpos() - 10);
    m_timeEdit.useSmallerFont(true);
    m_timeEdit.hideDeleteButton(true);
    m_timeEdit.setDataProvider([this] () -> const char* {
        if (m_systemCoreDelegate)
            return m_systemCoreDelegate->getTimeString();
        return nullptr;
    });

    m_timeButton.setXYpos(m_menuSplit.getLeftWidth() - 30 - 80, m_minsPerTokenEdit.getYpos() + m_minsPerTokenEdit.getHeight() + 60);
    m_timeButton.setIcon(s_editIcon);
    m_timeButton.setAction([this] () {
        if (m_eventDelegate) {
            m_authPass = [this] () {
                m_editPass = [this] () {
					if (m_eventDelegate) {
						const char* timeStr = m_editDialog.getText();
                        int timeLen = strlen(timeStr);
                        if (timeLen == 4) {
                            m_eventDelegate->settingsTimeChanged(timeStr);
                        }
					}
                };
                m_editFail = [this] () {
                };
                m_editDialog.setHeaderText("Enter time");
                m_editDialog.setTextLimit(4);
                m_eventDelegate->editDialogShow();
            };
            m_authFail = [this] () {
            };
            m_eventDelegate->authDialogShow();
        }
    });

    m_frontlight.setXYpos(m_dateEdit.getXpos(), m_dateEdit.getYpos() + m_dateEdit.getHeight() + 40);
    m_frontlight.setName("Enable Frontlight");
    if (m_systemCoreDelegate) {
        if (m_systemCoreDelegate->frontlightEnabled())
            m_frontlight.setOn();
        else
            m_frontlight.setOff();
    }
    m_frontlight.setAction([this] (bool switchOn) {
        if (m_eventDelegate)
            m_eventDelegate->settingsFrontlightEnabled(switchOn);
    });

    m_frontlightPrev.setXYpos(m_frontlight.getXpos() + m_frontlight.getWidth() + 30, m_dateEdit.getYpos() + m_dateEdit.getHeight() + 30);
    m_frontlightPrev.setText("<");
    m_frontlightPrev.setAction([this] () {
        if (m_eventDelegate) {
            m_eventDelegate->settingsFrontlightLevelChanged(-10);
        }
    });

    m_frontlightNext.setXYpos(m_menuSplit.getLeftWidth() - 30 - 80, m_dateEdit.getYpos() + m_dateEdit.getHeight() + 30);
    m_frontlightNext.setText(">");
    m_frontlightNext.setAction([this] () {
        if (m_eventDelegate) {
            m_eventDelegate->settingsFrontlightLevelChanged(+10);
        }
    });

    m_frontlightPercent.setXYpos(m_frontlightPrev.getXpos() + m_frontlightPrev.getWidth() + 10, m_dateEdit.getYpos() + m_dateEdit.getHeight() + 30);
    m_frontlightPercent.setWidth(m_frontlightNext.getXpos() - (m_frontlightPrev.getXpos() + m_frontlightPrev.getWidth()) - 20);
    m_frontlightPercent.setTextOffset(-10);
    m_frontlightPercent.hideDeleteButton(true);
    m_frontlightPercent.useSmallerFont(true);
    m_frontlightPercent.setDataProvider([this] () -> const char* {
        if (m_systemCoreDelegate)
            return m_systemCoreDelegate->getFrontlightLevelString();
        return nullptr;
    });

    m_webserver.setXYpos(m_frontlight.getXpos(), m_frontlight.getYpos() + m_frontlight.getHeight() + 40);
    m_webserver.setName("Enable Web interface");
    m_webserver.setAction([this] (bool switchOn) {
        //
    });


    m_changePin.setXYpos(m_webserver.getXpos(), m_headerSplit.getTopHeight() + m_headerSplit.getBottomHeight() - 80 - 30);
    m_changePin.setWidth((m_frontlight.getWidth() - 20) / 2);
    m_changePin.setTextOffset(0);
    m_changePin.setText("Set PIN");
    m_changePin.setAction([this] () {
        if (m_eventDelegate) {
            m_authPass = [this] () {
                m_editPass = [this] () {
                    if (m_eventDelegate) {
                        m_eventDelegate->settingsUpdatePIN(m_editDialog.getText());
                        m_okDialog.setHeaderText("Info");
                        m_okDialog.setInfoText("PIN changed");
                        m_eventDelegate->okDialogShow();
                    }
                };
                m_editFail = [this] () {
                };
                m_editDialog.setHeaderText("Enter new PIN");
                m_editDialog.setTextLimit(6);
                m_eventDelegate->editDialogShow();
            };
            m_authFail = [this] () {
            };
            m_eventDelegate->authDialogShow();
        }
    });

    m_factoryReset.setXYpos(m_changePin.getXpos() + m_changePin.getWidth() + 20, m_headerSplit.getTopHeight() + m_headerSplit.getBottomHeight() - 80 - 30);
    m_factoryReset.setWidth((m_frontlight.getWidth() - 20) / 2);
    m_factoryReset.setTextOffset(30);
    m_factoryReset.setText("Reset");
    m_factoryReset.setAction([this] () {
        if (m_eventDelegate) {
            m_authPass = [this] () {
                m_eventDelegate->settingsFactoryReset();
                m_okDialog.setHeaderText("Info");
                m_okDialog.setInfoText("Reset complete");
                m_eventDelegate->okDialogShow();
            };
            m_authFail = [this] () {
            };
            m_eventDelegate->authDialogShow();
        }
    });

    m_about.setXYpos(m_headerSplit.getXpos() + 60 + m_frontlight.getWidth() + 30, m_headerSplit.getTopHeight() + m_headerSplit.getBottomHeight() - 85);
    m_about.setWidth(m_menuSplit.getLeftWidth() - (60 + m_frontlight.getWidth() + 60));
    m_about.setFont(&FreeSans12pt7b);
    m_about.setTextAlignment(TextAlignment::Right);
    m_about.setText("Inkplate Dashboard\nVersion: 1.0\nPeculiar Technologies 2023");

    m_authDialog.setEventDelegate(m_eventDelegate);
    m_authDialog.create(width, height);
    m_authDialog.setHeaderText("Enter PIN");
    m_authDialog.setTextLimit(6);
    m_authDialog.setSecureMode(true);
    m_authDialog.setActions([this] () {
        if (m_eventDelegate)
            m_eventDelegate->authDialogHide(m_authDialog.getText()); 
    },
    [this] () {
        if (m_eventDelegate)
            m_eventDelegate->authDialogHide(nullptr); 
    });

    m_editDialog.setEventDelegate(m_eventDelegate);
    m_editDialog.create(width, height);
    m_editDialog.setActions([this] () {
        if (m_eventDelegate)
            m_eventDelegate->editDialogHide(m_editDialog.getText()); 
    },
    [this] () {
        if (m_eventDelegate)
            m_eventDelegate->editDialogHide(nullptr); 
    });

    m_okDialog.setEventDelegate(m_eventDelegate);
    m_okDialog.create(width, height);
    m_okDialog.setActions([this] () {
        if (m_eventDelegate)
            m_eventDelegate->okDialogHide(); 
    });

#if CONFIG_DEV_MODE_ON
    m_dumpDiag.setXYpos(m_menuBack.getXpos(), m_menuBack.getYpos() + m_menuBack.getHeight() + 10);
    m_dumpDiag.setText("D");
    m_dumpDiag.setAction([this] () {
        if (m_eventDelegate) {
            m_eventDelegate->dumpDiagnostics();
        }
    });
#endif
}

bool SettingsView::render(Inkplate* context) {
    bool renderView = true;
    bool forceCache = false;

    if (m_showAuthDialog || m_showEditDialog || m_showOKDialog)
        renderView = false;

    if (m_cacheView) {
        renderView = true;
        forceCache = true;
    }

	if (renderView) {
        m_menuSplit.render(context);
        m_headerSplit.render(context);
        m_menuName.render(context);
        m_menuBack.render(context);
        m_battery.render(context);
        m_minsPerTokenLabel.render(context);
        m_minsPerTokenEdit.render(context);
        m_minsPerTokenButton.render(context);
        m_dateLabel.render(context);
        m_dateEdit.render(context);
        m_dateButton.render(context);
        m_timeLabel.render(context);
        m_timeEdit.render(context);
        m_timeButton.render(context);
        m_frontlight.render(context);
        m_frontlightPrev.render(context);
        m_frontlightNext.render(context);
        m_frontlightPercent.render(context);
        m_webserver.render(context);
        m_changePin.render(context);
        m_factoryReset.render(context);
        m_about.render(context);
    #if CONFIG_DEV_MODE_ON
        m_dumpDiag.render(context);
    #endif
	    if (m_cacheView) {
            if (m_showAuthDialog) {
                m_authDialog.clearBackground(context);
                m_authDialog.render(context);
            } else if (m_showEditDialog) {
                m_editDialog.clearBackground(context);
                m_editDialog.render(context);
            } else if (m_showOKDialog) {
                m_okDialog.clearBackground(context);
                m_okDialog.render(context);
            }

            m_cacheView = false;
        }
    } else {
        if (m_showAuthDialog) {
	        m_authDialog.render(context);
        } else if (m_showEditDialog) {
			m_editDialog.render(context);
        } else if (m_showOKDialog) {
            m_okDialog.render(context);
		}
    }

	return forceCache;
}

bool SettingsView::touch(Inkplate* context) {
    bool res = false;
	if (m_showAuthDialog) {
        res |= m_authDialog.touch(context);
    } else if (m_showEditDialog) {
        res |= m_editDialog.touch(context);
    } else if (m_showOKDialog) {
        res |= m_okDialog.touch(context);
    } else {
        res |= m_menuBack.touch(context);
        res |= m_minsPerTokenButton.touch(context);
        res |= m_dateButton.touch(context);
        res |= m_timeButton.touch(context);
        res |= m_frontlight.touch(context);
        res |= m_frontlightPrev.touch(context);
        res |= m_frontlightNext.touch(context);
        // res |= m_webserver.touch(context);
        res |= m_changePin.touch(context);
        res |= m_factoryReset.touch(context);
    #if CONFIG_DEV_MODE_ON
        res |= m_dumpDiag.touch(context);
    #endif
    }
    return res;
}