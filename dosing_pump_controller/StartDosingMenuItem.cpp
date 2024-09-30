//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "StartDosingMenuItem.h"

StartDosingMenuItem::StartDosingMenuItem(const PumpController& pump1_controller, const PumpController& pump2_controller, const PumpController& pump3_controller)
: MenuItem("Start Dosing", false), pump1_controller(pump1_controller), pump2_controller(pump2_controller), pump3_controller(pump3_controller) {}

void StartDosingMenuItem::showFeature() {
    // This is kind of messy and we can clean this up with some additional methods to reduce the duplicate code, but thats a problem for the future.
    display->lcd.clear();
    display->lcd.print(dosing_message);
    display->lcd.setCursor(display->columns - pump1_title.length() - off_message.length(), 0);
    display->lcd.print(pump1_title);
    display->lcd.print(pump1_controller.getDosingEnabled() ? on_message : off_message);
    display->lcd.setCursor(0,1);
    display->lcd.print(pump2_title);
    display->lcd.print(pump2_controller.getDosingEnabled() ? on_message : off_message);
    display->lcd.setCursor(display->columns - pump3_title.length() - off_message.length(), 1);
    display->lcd.print(pump3_title);
    display->lcd.print(pump3_controller.getDosingEnabled() ? on_message : off_message);
}

void StartDosingMenuItem::presentableWillPerform() {
    unsigned long current_time = millis();
    pump1_controller.startDosing(current_time);
    pump2_controller.startDosing(current_time);
    pump3_controller.startDosing(current_time);
}

void StartDosingMenuItem::presentableWillDismiss() {
    pump1_controller.stopDosing();
    pump2_controller.stopDosing();
    pump3_controller.stopDosing();
}

void StartDosingMenuItem::leftAction() {}

void StartDosingMenuItem::rightAction() {}

void StartDosingMenuItem::selectAction() {
    completePresentation();
}
