//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef PrimePumpMenuItem_h
#define PrimePumpMenuItem_h

#include <Arduino.h>
#include <MenuItem.h>
#include "PumpController.h"

// A MenuItem that allows a user to prime a pump for any length of time decided by the user.
class PrimePumpMenuItem : public MenuItem {
    public:
        // Constructor creates a PrimePumpMenuItem.
        // @param pump_controller: The PumpController used to turn the pump on and off.
        PrimePumpMenuItem(PumpController& pump_controller);
    private:
        const String start_message = "-> Start"; // A Feature message to be displayed to the user during the start Feature state.
        const String stop_message = "-> Stop"; // A Feature message to be displayed to the user during the stop Feature state.
        const PumpController& pump_controller;
        // The possible states the feature can be in.
        // `start`: The pump is off and waiting for the user to start the pump.
        // `stop`: The pump is on and waiting for the user to stop the pump.
        enum FeatureState { start, stop };

        // The current state of the Feature being presented.
        FeatureState feature_state = start;

        // Displays the current Feature state.
        void showFeature();

        // Resets the Feature state.
        void presentableWillDismiss();

        // Required method, unused
        void leftAction();

        // Required method, unused
        void rightAction();

        // Turns the pump on or off depending on the current Feature state.
        void selectAction();
};
#endif
