//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef StartDosingMenuItem_h
#define StartDosingMenuItem_h

#include <Arduino.h>
#include <MenuItem.h>
#include "PumpController.h"

// A MenuItem that starts each dosing pump schedule and displays the pump status.
class StartDosingMenuItem : public MenuItem {
    public:
        // Constructor creates a StartDosingPumpMenu.
        // @param pump1_controller: The PumpController used to control pump 1.
        // @param pump2_controller: The PumpController used to control pump 2.
        // @param pump3_controller: The PumpController used to control pump 3.
        StartDosingMenuItem(PumpController& pump1_controller, PumpController& pump2_controller, PumpController& pump3_controller);
    private:
        PumpController& pump1_controller; // The PumpController used to control pump 1.
        PumpController& pump2_controller; // The PumpController used to control pump 2.
        PumpController& pump3_controller; // The PumpController used to control pump 3.
        const String dosing_message = "Dosing"; // Feature message to be displayed to the user while dosing.
        const String on_message = "On"; // Feature message to be displayed next to pumps that are enabled.
        const String off_message = "Off"; // Feature message to be displayed next to pumps that have not been enabled.
        const String pump1_title = "P1: "; // Feature message used to display pump 1 status.
        const String pump2_title = "P2: "; // Feature message used to display pump 2 status.
        const String pump3_title = "P3: "; // Feature message used to display pump 3 status.
        
        // Displays dosing pump status. 
        void showFeature();

        // Starts each dosing pump schedule.
        void presentableWillPerform();

        // Stops each dosing pump schedule.
        void presentableWillDismiss();
        
        // Required method, unused.
        void leftAction();

        // Required method, unused.
        void rightAction();

        // Returns to the main menu. 
        void selectAction();
};
#endif
