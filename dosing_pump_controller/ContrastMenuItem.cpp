//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "ContrastMenuItem.h"

ContrastMenuItem::ContrastMenuItem(DisplayController& display_controller)
: MenuItem("Contrast", false), display_controller(display_controller) {}

void ContrastMenuItem::showFeature() {
    display->lcd.clear();
    display->lcd.print(input_message);
    display->lcd.print(display_controller.currentContrast());
}

void ContrastMenuItem::presentableWillDismiss() {}

void ContrastMenuItem::leftAction() {
    display_controller.decreaseContrast();
}

void ContrastMenuItem::rightAction() {
    display_controller.increaseContrast();
}

void ContrastMenuItem::selectAction() {
    display_controller.saveContrast();
    completePresentation();
}
