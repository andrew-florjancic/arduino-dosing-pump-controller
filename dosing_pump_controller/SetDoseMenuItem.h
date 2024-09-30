//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef SetDoseMenuItem_h
#define SetDoseMenuItem_h

#include <Arduino.h>
#include <MenuItem.h>
#include <DoublyLinkedList.h>
#include "PumpController.h"

// A MenuItem that allows the user to set dose frequency and dose duration. 
class SetDoseMenuItem : public MenuItem {
    public:
        // Constructor creates a SetDoseMenuItem.
        // @param pump_controller: The PumpController that will be used to update and save pump settings.
        SetDoseMenuItem(const PumpController& pump_controller);
    private:
        // A menu of frequency options the user can choose.
        DoublyLinkedList<uint8_t> frequency_menu = DoublyLinkedList<uint8_t>();
        const String frequency_message = "Doses/Day: "; // Feature message to be displayed while the user is setting the dose frequency.
        const String dose_message = "Dose: "; // Feature message to be displayed while the user is setting the dose duration.
        const String complete_message = "Doses set"; // Feature message to be displayed at the end of the Feature.
        const PumpController pump_controller; // The PumpController that will be used to update and save pump settings.

        // Possible states the Feature can be in while presenting.
        enum FeatureState { frequency, dose_hundreds, dose_tens, dose_ones, complete };
        FeatureState feature_state = frequency;  // The current state of the Feature presentation.
        unsigned long dose_quantity = 0; // The current dose quantity, in milliliters, which will be set by the user.

        // Shows the current state of the set dose Feature.
        void showFeature();

        // Resets the Feature state and dose duration.
        void presentableWillDismiss();

        // Used to decrease the dose frequency or dose duration values depending on the Feature state.
        void leftAction();

        // Used to increase the dose frequency or dose duration values depending on the Feature state.
        void rightAction();

        // Confirms the current dose settings and advances the presentation to the next Feature state.
        void selectAction();

        // Advances the Feature state to the next state.
        nextState();
        
        // Decrements the dose quantity by the provided value. If the new dose_duration would be below 0, then no change occurs.
        void decrementDoseBy(uint8_t value);

        // Increments the dose quantity by the provided value. If the new dose quantity would exceed the time between doses, then no change occurs.
        void incrementDoseBy(uint8_t value);

        unsigned long getDoseDuration();
};
#endif
