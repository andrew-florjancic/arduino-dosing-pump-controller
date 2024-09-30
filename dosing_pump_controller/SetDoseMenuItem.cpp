//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "SetDoseMenuItem.h"

SetDoseMenuItem::SetDoseMenuItem(const PumpController& pump_controller) : MenuItem("Set Dose", false), pump_controller(pump_controller) {
    // Add dosing frequency options
    frequency_menu.append(2);   // Dose every 12 hours
    frequency_menu.append(3);   // Dose every 8 hours
    frequency_menu.append(4);   // Dose every 6 hours
    frequency_menu.append(6);   // Dose every 4 hours
    frequency_menu.append(8);   // Dose every 3 hours
    frequency_menu.append(12);  // Dose every 2 hours
    frequency_menu.append(24);  // Dose every hour
    frequency_menu.append(48);  // Dose every 30 minutes
    frequency_menu.append(96);  // Dose every 15 minutes
    frequency_menu.append(192); // Dose every 7.5 minutes
    frequency_menu.setCurrentItem(pump_controller.getDoseFrequency());
}

void SetDoseMenuItem::showFeature() {
    display->lcd.clear();
    switch(feature_state) {
        case frequency: display->lcd.print(frequency_message + String(frequency_menu.getCurrentItem()->data)); break;
        case dose_hundreds:
        case dose_tens:
        case dose_ones: display->lcd.print(dose_message + String(dose_quantity)); break; 
        case complete: display->lcd.print(complete_message); break;
    }
}

void SetDoseMenuItem::presentableWillDismiss() {
     // Reset feature state and dose duration for the next presentation.
    feature_state = frequency;
    dose_quantity = 0;
}

void SetDoseMenuItem::leftAction() {
    switch(feature_state) {
        case frequency: frequency_menu.previousItem(); break;
        case dose_hundreds: decrementDoseBy(100); break;
        case dose_tens: decrementDoseBy(10); break;
        case dose_ones: decrementDoseBy(1); break;
    }
}

void SetDoseMenuItem::rightAction() {
        switch(feature_state) {
        case frequency: frequency_menu.nextItem(); break;
        case dose_hundreds: incrementDoseBy(100); break;
        case dose_tens: incrementDoseBy(10); break;
        case dose_ones: incrementDoseBy(1); break;
    }
}

void SetDoseMenuItem::selectAction() {
    if(feature_state == complete) {
        pump_controller.updateDoseFrequency(frequency_menu.getCurrentItem()->data);
        pump_controller.updateDoseDuration(getDoseDuration());
        completePresentation();
        return; 
    }
    nextState();
}

SetDoseMenuItem::nextState() {
    switch(feature_state) {
        case frequency: feature_state = dose_hundreds; break;
        case dose_hundreds: feature_state = dose_tens; break;
        case dose_tens: feature_state = dose_ones; break;
        case dose_ones: feature_state = complete; break;
        case complete: feature_state = frequency; break;
    }
}

void SetDoseMenuItem::decrementDoseBy(uint8_t value) {
    if(dose_quantity < value) { return; }
    dose_quantity -= value;
}

void SetDoseMenuItem::incrementDoseBy(uint8_t value) {
    if((getDoseDuration() + value) >= (pump_controller.day_length / frequency_menu.getCurrentItem()->data)) { return; }
    dose_quantity += value;
}

unsigned long SetDoseMenuItem::getDoseDuration() {
    return dose_quantity * 1000;
}
