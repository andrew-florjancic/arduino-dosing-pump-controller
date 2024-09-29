//  Created by Andrew Florjancic on 9/29/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef EnablePumpMenuItem_h
#define EnablePumpMenuItem_h

#include <MenuItem.h>
#include "PumpController.h"

// A Menu item that allows the user to enable or disable dosing for a pump.
class EnablePumpMenuItem : public MenuItem {
    private:
        // The PumpController used to update the enable pump setting.
        PumpController& pump_controller;

        // True if the pump should be enabled while dosing.
        bool is_enabled;

        // A message displayed to the user when selecting the pump enabled status.
        const String input_message = "Dosing: ";
        // A message displayed to the user when the current is_enabled value is true.
        const String on_message = "On";
        // A message displayed to the user when the current is_enabled value is false.
        const String off_message = "Off";

        // Shows the is_enabled pump status.
        void showFeature();

        // Required method, unused.
        void presentableWillDismiss();
        
        // Sets the is_enabled value to false.
        void leftAction();

        // Sets the is_enabled value to true.
        void rightAction();

        // Updated the current is_enabled value and saves the pump setting.
        void selectAction();
    public:

        // Constructor creates a EnablePumpMenuItem.
        // @param pump_controller: The PumpController used to update the dosing_enabled pump setting.
        EnablePumpMenuItem(PumpController& pump_controller);
};
#endif
