//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef ResetPumpSettingsMenuItem_h
#define ResetPumpSettingsMenuItem_h

#include <Arduino.h>
#include <MenuItem.h>
#include "PumpController.h"

// A MenuItem that allows the user to reset a pumps settings to the factory default values.
class ResetPumpSettingsMenuItem : public MenuItem {
    public:
        // Constructor creates a ResetPumpSettingsMenuItem.
        ResetPumpSettingsMenuItem(const PumpController& pump_controller);
    private:
        const PumpController pump_controller; // The PumpController used to reset pump settings.
        const String confirmation_message = "Confirm: "; // A Feature message to be displayed to the user when confirming pump reset.
        const String yes_message = "Yes"; // A Feature message to be displayed to the user when they have selected to confirm the reset.
        const String no_message = "No"; // A Feature message to be displayed to the user when they have selected to cancel the reset.
        bool confirm_reset = true; // Confirmiation from the user that the pump settings should be reset. Default to true.

        // Displays the current value of the confirm reset boolean.
        void showFeature();

        // Resets the confrim reset state.
        void presentableWillDismiss() override;

        // Updates the confirm reset value to false.
        void leftAction() override;

        // Updates the confirm reset value to true.
        void rightAction() override;

        // Resets the pump settings if the confirm reset value is true then dismisses the Feature.
        void selectAction();
};
#endif
