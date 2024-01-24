//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include <functional>

#include "config.hpp"
#include "Widget.hpp"

class Inkplate;

class TokenWidget : public Widget {
public:
    TokenWidget() {}
    ~TokenWidget() {};

    using TokenProvider = std::function<const char*()>;
    void setDataProvider(TokenProvider fetchTokensString);

public: // Widget

    int getWidth() override;
    int getHeight() override;

    bool render(Inkplate* context) override;

private:

    TokenProvider   m_fetchTokensString = nullptr;
};