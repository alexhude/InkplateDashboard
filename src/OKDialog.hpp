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

class OKDialog : public View {
public:
    OKDialog() {};
    ~OKDialog() {};

    void clearBackground(Inkplate* context);

    void setHeaderText(const char* text);
    void setInfoText(const char* text);

    using ActionHandler = std::function<void()>;
    void setActions(ActionHandler okAction);

public: // View

    const char* getName() override { return "OKDialog"; }

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
    ButtonWidget        m_ok;
};