//
//  Copyright (c) 2023, Alexander Hude
//  All rights reserved.
//

#pragma once

#include "config.hpp"

class View;

class ViewControllerDelegate {
public:
    virtual View* getCurrentView() = 0;
    virtual void showMainView() = 0;
    virtual void showScreenTimeView() = 0;
    virtual void showTokensView() = 0;
    virtual void showActivityListView() = 0;
    virtual void showSettingsView() = 0;

    virtual void showAuthDialog() = 0;
    virtual void hideAuthDialog(bool pass) = 0;

    virtual void showEditDialog() = 0;
    virtual void hideEditDialog(bool pass) = 0;

    virtual void showConfirmDialog() = 0;
    virtual void hideConfirmDialog(bool pass) = 0;

    virtual void showOKDialog() = 0;
    virtual void hideOKDialog() = 0;

    virtual void dumpDiagnostics() = 0;
};