//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#include "Inkplate.h"
#include "Fonts/FreeSansBold18pt7b.h"
#include "Fonts/FreeSansBold12pt7b.h"

#include "Banner.hpp"

#include "helper.hpp"

void Banner::setHeaderText(const char* text) {
	m_headerText.setText(text);
}

void Banner::setInfoText(const char* text) {
	m_infoText.setText(text);
}

void Banner::create(int width, int height) {
    m_headerSplit.setXYpos((width - s_width)/2, (height - s_height)/2);
    m_headerSplit.setArea(s_width, s_height);
    m_headerSplit.setOffset(80);

    int dlgXpos = m_headerSplit.getXpos();
    int dlgYpos = m_headerSplit.getYpos();

    m_headerText.setXYpos(dlgXpos+30, dlgYpos+60);
    m_headerText.setFont(&FreeSansBold18pt7b);

	m_infoText.setXYpos(dlgXpos+30, dlgYpos + m_headerSplit.getTopHeight() + 60);
	m_infoText.setWidth(s_width - 60);
	m_infoText.setFont(&FreeSansBold12pt7b);
	m_infoText.setTextAlignment(TextAlignment::Center);
}

bool Banner::render(Inkplate* context) {
    int dlgXpos = m_headerSplit.getXpos();
    int dlgYpos = m_headerSplit.getYpos();

	context->drawRect(dlgXpos+1, dlgYpos+1, s_width-2, s_height-2, BLACK);
    context->drawThickLine(dlgXpos + 5, dlgYpos + s_height, dlgXpos + 2 + s_width, dlgYpos + s_height, BLACK, 4);
    context->drawThickLine(dlgXpos + s_width, dlgYpos + 5, dlgXpos + s_width, dlgYpos + 2 + s_height, BLACK, 4);

    m_headerSplit.render(context);
	m_infoText.render(context);
    m_headerText.render(context);
    return false;
}

bool Banner::touch(Inkplate* context) {
    bool res = false;
    return res;
}
