//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "ResetPumpSettingsMenuItem.h"

ResetPumpSettingsMenuItem::ResetPumpSettingsMenuItem(PumpController& pump_controller) : pump_controller(pump_controller), MenuItem("Reset", false) {}

void ResetPumpSettingsMenuItem::showFeature() {
    display->lcd.clear();
    display->lcd.print(confirmation_message);
    display->lcd.print(confirm_reset ? yes_message : no_message);
}

void ResetPumpSettingsMenuItem::presentableWillDismiss() {
    confirm_reset = true;
}

void ResetPumpSettingsMenuItem::leftAction() {
    confirm_reset = false;
}

void ResetPumpSettingsMenuItem::rightAction() {
    confirm_reset = true;
}

void ResetPumpSettingsMenuItem::selectAction() {
    if(confirm_reset) { pump_controller.resetPumpSettings(); }
    completePresentation();
}
