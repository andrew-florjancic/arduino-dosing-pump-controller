//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "PrimePumpMenuItem.h"

PrimePumpMenuItem::PrimePumpMenuItem(PumpController& pump_controller) : MenuItem("Prime", false), pump_controller(pump_controller) {}

void PrimePumpMenuItem::showFeature() {
    display->lcd.clear();
    switch (feature_state) {
        case start: display->lcd.print(start_message); break;
        case stop: display->lcd.print(stop_message); break;
    }
}

void PrimePumpMenuItem::presentableWillDismiss() {
    feature_state = start;
}

void PrimePumpMenuItem::leftAction() {}

void PrimePumpMenuItem::rightAction() {}

void PrimePumpMenuItem::selectAction() {
    switch(feature_state) {
        case start:
            pump_controller.activate();
            feature_state = stop;
            break;
        case stop:
            pump_controller.deactivate();
            completePresentation();
            break;
    }
}
