//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"
#include "View.hpp"
#include "SeparatorWidget.hpp"
#include "LabelWidget.hpp"
#include "ButtonWidget.hpp"

class ConfirmDialog : public View {
public:
    ConfirmDialog() {};
    ~ConfirmDialog() {};

    void clearBackground(Inkplate* context);

    void setHeaderText(const char* title);

    using ActionHandler = std::function<void()>;
    void setActions(ActionHandler okAction, ActionHandler cancelAction);

public: // View

    const char* getName() override { return "ConfirmDialog"; }

    void create(int width, int height) override;
    bool render(Inkplate* context) override;
    bool touch(Inkplate* context) override;

private:

    static const int s_width = 340;
    static const int s_height = 200;
    static const unsigned char s_okIcon[];
    static const unsigned char s_cancelIcon[];

    SeparatorWidget     m_headerSplit { SeparatorType::BottomOffset };

    LabelWidget         m_headerText;
    ButtonWidget        m_ok;
    ButtonWidget        m_cancel;
};