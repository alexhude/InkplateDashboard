//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeSansBoldOblique24pt7b.h"
#include "Fonts/FreeSerifBoldItalic24pt7b.h"
#include "Fonts/FreeMonoBold12pt7b.h"
#include "Fonts/FreeSansBold18pt7b.h"
#include "Fonts/FreeSansBold12pt7b.h"

#include "EventManagerDelegate.hpp"
#include "SystemCoreDelegate.hpp"
#include "ProfileManagerDelegate.hpp"
#include "ActivityListView.hpp"

#include "helper.hpp"

const unsigned char ActivityListView::s_backIcon [] PROGMEM = {
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

const unsigned char ActivityListView::s_importIcon [] PROGMEM = {
	0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xf0, 
	0xfe, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xf0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 
	0xfe, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xf0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xf0, 
	0xfe, 0x0f, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xf0, 0xfe, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xf0, 
	0xfe, 0x0f, 0xff, 0xff, 0xc0, 0x80, 0x3f, 0xf0, 0xfe, 0x0f, 0xff, 0xff, 0xc0, 0xc0, 0x1f, 0xf0, 
	0xfe, 0x0f, 0xff, 0xff, 0xc0, 0xe0, 0x0f, 0xf0, 0xfe, 0x0f, 0xff, 0xff, 0xc0, 0xf8, 0x07, 0xf0, 
	0xfe, 0x0f, 0xff, 0xff, 0xc0, 0xfc, 0x03, 0xf0, 0xfe, 0x0f, 0xff, 0xff, 0xc0, 0xfe, 0x01, 0xf0, 
	0xfe, 0x0f, 0xff, 0xff, 0xc0, 0xff, 0x00, 0xf0, 0xfe, 0x0f, 0xff, 0xff, 0xc0, 0xff, 0x80, 0x70, 
	0xfe, 0x0f, 0xff, 0xff, 0xc0, 0xff, 0xc0, 0x30, 0xfe, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x10, 
	0xfe, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x10, 0xfe, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x10, 
	0xfe, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x10, 0xfe, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x10, 
	0xfe, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x10, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x10, 
	0xfe, 0x0f, 0xf7, 0xff, 0xff, 0xff, 0xfc, 0x10, 0xfe, 0x0f, 0xc1, 0xff, 0xff, 0xff, 0xfc, 0x10, 
	0xfe, 0x0f, 0xc0, 0xff, 0xff, 0xff, 0xfc, 0x10, 0xfe, 0x0f, 0xc0, 0x7f, 0xff, 0xff, 0xfc, 0x10, 
	0xfe, 0x0f, 0xc0, 0x3f, 0xff, 0xff, 0xfc, 0x10, 0xfe, 0x0f, 0xe0, 0x1f, 0xff, 0xff, 0xfc, 0x10, 
	0xfe, 0x0f, 0xf0, 0x0f, 0xff, 0xff, 0xfc, 0x10, 0xfe, 0x0f, 0xf8, 0x07, 0xff, 0xff, 0xfc, 0x10, 
	0xff, 0x1f, 0xfc, 0x03, 0xff, 0xff, 0xfc, 0x10, 0xff, 0xff, 0xfe, 0x01, 0xff, 0xff, 0xfc, 0x10, 
	0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xfc, 0x10, 0xff, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xfc, 0x10, 
	0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xfc, 0x10, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xfc, 0x10, 
	0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xfc, 0x10, 0xc0, 0x00, 0x00, 0x00, 0x07, 0xff, 0xfc, 0x10, 
	0x80, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x10, 0x80, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x10, 
	0x80, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x10, 0x80, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x10, 
	0xc0, 0x00, 0x00, 0x00, 0x07, 0xff, 0xfc, 0x10, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xfc, 0x10, 
	0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xfc, 0x10, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xfc, 0x10, 
	0xff, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xfc, 0x10, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xfc, 0x10, 
	0xff, 0xff, 0xfe, 0x01, 0xff, 0xff, 0xfc, 0x10, 0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xfc, 0x10, 
	0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xfc, 0x10, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xfc, 0x10, 
	0xff, 0xff, 0xe0, 0x1f, 0x80, 0x00, 0x00, 0x10, 0xff, 0xff, 0xc0, 0x3f, 0x00, 0x00, 0x00, 0x10, 
	0xff, 0xff, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x10, 0xff, 0xff, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x10, 
	0xff, 0xff, 0xc1, 0xff, 0x00, 0x00, 0x00, 0x10, 0xff, 0xff, 0xf7, 0xff, 0x80, 0x00, 0x00, 0x30
};

const unsigned char ActivityListView::s_clearIcon [] PROGMEM = {
	0xff, 0xff, 0xff, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0x00, 0x03, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xf8, 0x00, 0x01, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0x00, 0x00, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xe0, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xe0, 0x7f, 0xe0, 0x7f, 0xff, 0xf0, 
	0xff, 0xff, 0xe0, 0xff, 0xf0, 0x7f, 0xff, 0xf0, 0xff, 0xff, 0xe1, 0xff, 0xf8, 0x3f, 0xff, 0xf0, 
	0xff, 0xff, 0xe1, 0xff, 0xf8, 0x3f, 0xff, 0xf0, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 
	0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 
	0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 
	0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 
	0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 
	0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xff, 0x83, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xf0, 
	0xff, 0x83, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xf0, 0xff, 0x83, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xf0, 
	0xff, 0x83, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 
	0xff, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x1f, 0xf0, 0xff, 0x83, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xf0, 
	0xff, 0x83, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xf0, 0xff, 0x83, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xf0, 
	0xff, 0x83, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xf0, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 
	0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 
	0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xff, 0xf0
};

const char* ActivityListView::s_weekDays[7] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

void ActivityListView::setProfileDelegate(ProfileManagerDelegate* delegate) {
	m_profileDelegate = delegate;
}

bool ActivityListView::showsDialog() {
	return m_showAuthDialog || m_showOKDialog;
}

void ActivityListView::showAuthDialog() {
	m_authDialog.reset();
    m_showAuthDialog = true;
    m_cacheView = true;
}

void ActivityListView::hideAuthDialog(bool pass) {
    m_showAuthDialog = false;
    if (pass)
        m_authPass();
    else
        m_authFail();
}

void ActivityListView::showOKDialog() {
    m_showOKDialog = true;
    m_cacheView = true;
}

void ActivityListView::hideOKDialog() {
    m_showOKDialog = false;
}

void ActivityListView::create(int width, int height) {
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

    m_menuName.setXYpos(m_headerSplit.getXpos()+30, m_headerSplit.getYpos() + 60);
    m_menuName.setFont(&FreeSansBoldOblique24pt7b);
    m_menuName.setText("Activity List");

	m_profileSplit.setXYpos(0, m_headerSplit.getTopHeight());
	m_profileSplit.setArea(m_menuSplit.getLeftWidth(), m_headerSplit.getBottomHeight());

    int p_xbase = m_profileSplit.getXpos();

    for (int p = 0; p < m_maxProfileCount; p++) {
	    int p_ybase = m_profileSplit.getYpos();

		m_activitySplit[p].setXYpos(p_xbase, p_ybase);
	   	m_activitySplit[p].setArea(m_profileSplit.getLeftWidth(), m_headerSplit.getBottomHeight());
    	m_activitySplit[p].setOffset(140);

		// profile name
        m_names[p].setXYpos(p_xbase + 30, p_ybase + 60);
        m_names[p].setDataProvider([p, this] () -> const char* {
            if (m_profileDelegate) {
                return m_profileDelegate->getName(p);
            }
            return nullptr;
        });

		p_ybase += 90;

		// change week day
		m_prevDay[p].setXYpos(p_xbase + 30, p_ybase);
		m_prevDay[p].setText("<");
		m_prevDay[p].setAction([p, this] () {
			if (m_weekDayIndex[p] == 0)
				m_weekDayIndex[p] = 6;
			else
				m_weekDayIndex[p]--;
		});
		m_nextDay[p].setXYpos(p_xbase + m_profileSplit.getLeftWidth() - m_prevDay[p].getWidth() - 30, p_ybase);
		m_nextDay[p].setText(">");
		m_nextDay[p].setAction([p, this] () {
			if (m_weekDayIndex[p] == 6)
				m_weekDayIndex[p] = 0;
			else
				m_weekDayIndex[p]++;
		});

		m_weekDay[p].setXYpos(p_xbase + 30 + m_prevDay[p].getWidth() + 20, p_ybase + m_prevDay[p].getHeight() - 30);
		m_weekDay[p].setWidth(m_nextDay[p].getXpos() - (m_prevDay[p].getXpos() + m_prevDay[p].getWidth()) - 40);
		m_weekDay[p].setFont(&FreeSansBold18pt7b);
		m_weekDay[p].setTextAlignment(TextAlignment::Center);

		p_ybase += m_prevDay[p].getHeight();

		// activity list
        m_activity[p].setXYpos(p_xbase + 30, p_ybase);
        m_activity[p].setWidth(m_profileSplit.getLeftWidth() - 60);
        m_activity[p].setHeight(m_activitySplit[p].getYpos() + m_activitySplit[p].getTopHeight() - p_ybase);
        m_activity[p].setDataProvider([p, this] (int idx, int* mins, const char** text) -> bool {
            if (m_profileDelegate) {
                return m_profileDelegate->getActivity(p, idx, mins, text, m_weekDayIndex[p]);
			}
            return false; 
        });

		p_ybase = m_activitySplit[p].getYpos() + m_activitySplit[p].getTopHeight() + 30;

		m_importHeader[p].setXYpos(p_xbase + 30, p_ybase + 20);
		m_importHeader[p].setFont(&FreeSansBold12pt7b);
		m_importHeader[p].setText("Import list from");

		m_import[p].setXYpos(p_xbase + m_profileSplit.getLeftWidth() - 30 - 80 - 10 - 80, p_ybase);
		m_import[p].setIcon(s_importIcon);
		m_import[p].setAction([p, this] () {
			if (m_eventDelegate) {
				m_authPass = [p, this] () {
					if (m_eventDelegate) {
						const char* errStr = "Internal Error";
						bool res = m_eventDelegate->profileImportActivityList(p, &errStr);
						if (!res) {
							m_okDialog.setHeaderText("Error");
							m_okDialog.setInfoText(errStr);
						} else {
							m_okDialog.setHeaderText("Info");
							m_okDialog.setInfoText("Import complete");
						}
						m_eventDelegate->okDialogShow();
					}
				};
				m_authFail = [this] () {
				};
				m_eventDelegate->authDialogShow();
			}
		});

		m_clear[p].setXYpos(p_xbase + m_profileSplit.getLeftWidth() - 30 - 80, p_ybase);
		m_clear[p].setIcon(s_clearIcon);
		m_clear[p].setAction([p, this] () {
			if (m_eventDelegate) {
				m_authPass = [p, this] () {
					if (m_eventDelegate) {
						m_eventDelegate->profileClearAllActivities(p);
						m_okDialog.setHeaderText("Info");
						m_okDialog.setInfoText("Activity list cleared");
						m_eventDelegate->okDialogShow();
					}
				};
				m_authFail = [this] () {
				};
				m_eventDelegate->authDialogShow();
			}
		});

		p_ybase += 60;

		sprintf(m_importNameText[p], "/activity%.2d.txt", p);
		m_importName[p].setXYpos(p_xbase + 30, p_ybase);
		m_importName[p].setFont(&FreeMonoBold12pt7b);
		m_importName[p].setText(m_importNameText[p]);

		p_xbase += m_profileSplit.getLeftWidth();
	}

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

    m_okDialog.setEventDelegate(m_eventDelegate);
    m_okDialog.create(width, height);
    m_okDialog.setActions([this] () {
        if (m_eventDelegate)
            m_eventDelegate->okDialogHide(); 
    });
}

bool ActivityListView::render(Inkplate* context) {
    bool renderView = true;
    bool forceCache = false;

    if (m_showAuthDialog || m_showOKDialog)
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
		m_profileSplit.render(context);
		for (int p = 0; p < m_maxProfileCount; p++) {
			if (m_profileDelegate) {
				if (!m_profileDelegate->isActive(p))
					continue;
			}

			m_prevDay[p].render(context);
			m_nextDay[p].render(context);
			m_weekDay[p].setText(s_weekDays[m_weekDayIndex[p]]);
			m_weekDay[p].render(context);
			m_activitySplit[p].render(context);
			m_names[p].render(context);
			m_activity[p].render(context);
			m_importHeader[p].render(context);
			m_import[p].render(context);
			m_clear[p].render(context);
			m_importName[p].render(context);
		}

	    if (m_cacheView) {
			if (m_showAuthDialog) {
                m_authDialog.clearBackground(context);
                m_authDialog.render(context);
			} else if (m_showOKDialog) {
                m_okDialog.clearBackground(context);
                m_okDialog.render(context);
			}
            m_cacheView = false;
        }
    } else {
		if (m_showAuthDialog) {
    		m_authDialog.render(context);
        } else if (m_showAuthDialog) {
			m_okDialog.render(context);
		}
    }

	return forceCache;
}

bool ActivityListView::touch(Inkplate* context) {
    bool res = false;
	if (m_showAuthDialog) {
        res |= m_authDialog.touch(context);
    } else if (m_showOKDialog) {
        res |= m_okDialog.touch(context);
    } else {
		res |= m_menuBack.touch(context);
		for (int p = 0; p < m_maxProfileCount; p++) {
			res |= m_prevDay[p].touch(context);
			res |= m_nextDay[p].touch(context);
			res |= m_import[p].touch(context);
			res |= m_clear[p].touch(context);
		}
	}
    return res;
}