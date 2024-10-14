//  Created by Andrew Florjancic on 9/22/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "BrightnessMenuItem.h"

BrightnessMenuItem::BrightnessMenuItem(const DisplayController& display_controller)
: MenuItem("Brightness", false), display_controller(display_controller) {}

void BrightnessMenuItem::showFeature() {
    display->lcd.clear();
    display->lcd.print(input_message);
    display->lcd.print(display_controller.currentBrightness());
}

void BrightnessMenuItem::leftAction() {
    display_controller.decreaseBrightness();
}

void BrightnessMenuItem::rightAction() {
    display_controller.increaseBrightness();
}

void BrightnessMenuItem::selectAction() {
    display_controller.saveBrightness();
    completePresentation();
}
