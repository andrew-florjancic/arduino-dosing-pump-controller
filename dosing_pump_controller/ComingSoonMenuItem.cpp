//  Created by Andrew Florjancic on 10/12/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "ComingSoonMenuItem.h"

ComingSoonMenuItem::ComingSoonMenuItem(String title) : MenuItem(title, false) {}

void ComingSoonMenuItem::showFeature() {
    display->lcd.clear();
    display->lcd.print(display_message);
}

void ComingSoonMenuItem::presentableWillDismiss() {}

void ComingSoonMenuItem::leftAction() {}

void ComingSoonMenuItem::rightAction() {}

void ComingSoonMenuItem::selectAction() { completePresentation(); }
