//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef CalibratePumpMenuItem_h
#define CalibratePumpMenuItem_h

#include <Arduino.h>
#include <MenuItem.h>
#include "PumpController.h"

// A MenuItem that allows a user to set the duty cycle of a dosing pump and then turn the pump on for a calibration period. 
class CalibratePumpMenuItem : public MenuItem {
    public:
        // Constructor creates a CalibratePumpMenuItem.
        // @param: pump_controller: The PumpController that will be used to update pump settings and turn the pump on and off.
        CalibratePumpMenuItem(const PumpController& pump_controller);

        // To be called by the pump controller when the calibration period has ended to return control to the menu item. 
        void calibrationComplete();
    private:
        // The possible states the Feature can be in.
        // `input`: The user can set the PWM of the pump to adjust the amount dosed.
        // `calibrating`: The pump is calibrating and the user will have to wait until the calibration period is over.
        // `complete`: The calibration has ended and the user can return to the menu.
        enum FeatureState { input, calibrating, complete };
        FeatureState feature_state = input; // The current state of the Feature.
        const PumpController& pump_controller; // The PumpController used to update the duty cycle and calibrate the pump.
        // A Feature message to be displayed when the user is setting the duty cycle for the pump.
        const String input_message = "PWM: ";

        // A Feature message to be displayed while the pump is calibrating.
        const String calibrating_message = "Calibrating...";

        // A Feature message to be displayed during after calibration is complete.
        const String complete_message = "Complete";

        uint8_t duty_cycle; // The current duty cycle the pump will operate at.
        const uint8_t min_duty = 0; // Min value for the duty_cycle
        const uint8_t max_duty = 255; // Max value for the duty_cycle

        // Displays the current state of the Feature.
        void showFeature();

        // Resets the Feature state.
        void presentableWillDismiss();

        // Decrements the duty cylce during the input Feature state.
        void leftAction();

        // Increments the duty cycle during the input Feature state.
        void rightAction();

        // Selects the current action based on the current Feature state.
        void selectAction();
};

#endif