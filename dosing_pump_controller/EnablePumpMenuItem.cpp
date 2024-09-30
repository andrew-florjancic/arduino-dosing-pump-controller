//  Created by Andrew Florjancic on 9/29/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "EnablePumpMenuItem.h"

EnablePumpMenuItem::EnablePumpMenuItem(const PumpController& pump_controller) : MenuItem("Enable Pump", false), pump_controller(pump_controller) {
    is_enabled = pump_controller.getDosingEnabled();
}

void EnablePumpMenuItem::showFeature() {
    display->lcd.clear();
    display->lcd.print(input_message);
    display->lcd.print(is_enabled ? on_message : off_message);
}

void EnablePumpMenuItem::presentableWillDismiss() {}

void EnablePumpMenuItem::leftAction() {
    is_enabled = false;
}

void EnablePumpMenuItem::rightAction() {
    is_enabled = true;
}

void EnablePumpMenuItem::selectAction() {
    pump_controller.updateDosingEnabled(is_enabled);
    completePresentation();
}
