//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "CalibratePumpMenuItem.h"

CalibratePumpMenuItem::CalibratePumpMenuItem(const PumpController& pump_controller) : MenuItem("Calibrate", false), pump_controller(pump_controller) {
    duty_cycle = pump_controller.getDutyCycle();
}

void CalibratePumpMenuItem::showFeature() {
    display->lcd.clear();
    switch(feature_state) {
        case input: display->lcd.print(input_message + String(duty_cycle)); break;
        case calibrating: display->lcd.print(calibrating_message); break;
        case complete: display->lcd.print(complete_message); break;
    }
}

void CalibratePumpMenuItem::presentableWillDismiss() {
    feature_state = input;
}

void CalibratePumpMenuItem::leftAction() {
    if(feature_state != input) { return; }
    if(duty_cycle == min_duty) { return; }
    duty_cycle--;
}

void CalibratePumpMenuItem::rightAction() {
    if(feature_state != input) { return; }
    if(duty_cycle == max_duty) { return; }
    duty_cycle++;
}

void CalibratePumpMenuItem::selectAction() {
        switch(feature_state) {
        case input:
            feature_state = calibrating;
            pump_controller.updateDutyCycle(duty_cycle);
            pump_controller.calibrate(millis());
            break;
        case calibrating: break;
        case complete: completePresentation(); break;
    }
}

void CalibratePumpMenuItem::calibrationComplete() {
    feature_state = complete;
    showFeature();
}
