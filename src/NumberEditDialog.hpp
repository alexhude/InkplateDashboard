//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"
#include "View.hpp"
#include "SeparatorWidget.hpp"
#include "LabelWidget.hpp"
#include "EditTextWidget.hpp"
#include "ButtonWidget.hpp"

class NumberEditDialog : public View {
public:
    NumberEditDialog() {};
    ~NumberEditDialog() {};

    void reset();
    void clearBackground(Inkplate* context);

    char* getText();

    void setHeaderText(const char* title);
    void setTextLimit(int limit);
    void setSecureMode(bool secure);

    using ActionHandler = std::function<void()>;
    void setActions(ActionHandler okAction, ActionHandler cancelAction);

public: // View

    const char* getName() override { return "NumberEditDialog"; }

    void create(int width, int height) override;
    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const int s_width = 360;//340;
    static const int s_height = 590;
    static const unsigned char s_okIcon[];
    static const unsigned char s_cancelIcon[];

    SeparatorWidget     m_headerSplit { SeparatorType::TopOffset };

    LabelWidget         m_headerText;
    EditTextWidget      m_number;
    ButtonWidget        m_digits[10];
    ButtonWidget        m_ok;
    ButtonWidget        m_cancel;
};