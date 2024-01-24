//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"
#include "View.hpp"
#include "SeparatorWidget.hpp"
#include "LabelWidget.hpp"
#include "TextWidget.hpp"
#include "ButtonWidget.hpp"

class Banner : public View {
public:
    Banner() {};
    ~Banner() {};

    void setHeaderText(const char* text);
    void setInfoText(const char* text);

public: // View

    const char* getName() override { return "Banner"; }

    void create(int width, int height) override;
    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const int s_width = 460;
    static const int s_height = 250;
    static const unsigned char s_okIcon[];

    SeparatorWidget     m_headerSplit { SeparatorType::TopOffset };

    LabelWidget         m_headerText;
    TextWidget          m_infoText;
};