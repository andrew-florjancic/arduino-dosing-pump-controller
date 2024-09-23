//  Created by Andrew Florjancic on 9/23/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef ContrastMenuItem_h
#define ContrastMenuItem_h

#include <Arduino.h>
#include <MenuItem.h>
#include "DisplayController.h"

// A Menu item that allows the user to adjust and save the contrast setting.
class ContrastMenuItem : public MenuItem {
    public:
        // Constructor creates a ContrastMenuItem.
        // @param display_controller: The DisplayController that will be used to update and save contrast settings.
        ContrastMenuItem(DisplayController& display_controller);
    private:
        // The DisplayController used to update and save contrast settings.
        const DisplayController display_controller;

        // The message displayed to the user when selecting a contrast value.
        const String input_message = "Contrast: ";

        // Displays the current contrast level to the user.
        void showFeature();

        // Required method, unused.
        void presentableWillDismiss();
        
        // Decrements the contrast level.
        void leftAction();

        // Increments the contrast level.
        void rightAction();

        // Saves the current contrast level to stored device settings.
        void selectAction();
};
#endif
