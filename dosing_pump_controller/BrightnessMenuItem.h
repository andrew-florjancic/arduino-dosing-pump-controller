//  Created by Andrew Florjancic on 9/22/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef BrightnessMenuItem_h
#define BrightnessMenuItem_h

#include <Arduino.h>
#include <MenuItem.h>
#include "DisplayController.h"

// A Menu item that allows the user to adjust and save the brightness setting.
class BrightnessMenuItem : public MenuItem {
    private:
        // The DisplayController used to update and save brightness settings.
        const DisplayController display_controller;

        // The message displayed to the user when selecting a brightness value.
        const String input_message = "Brightness: ";

        // Displays the current brightness level to the user.
        void showFeature();

        // Required method, unused.
        void presentableWillDismiss();
        
        // Decrements the brightness level.
        void leftAction();

        // Increments the brightness level.
        void rightAction();

        // Saves the current brightness level to stored device settings.
        void selectAction();
    public:

        // Constructor creates a BrightnessMenuItem.
        // @param display_controller: The DisplayController that will be used to update and save brightness settings.
        BrightnessMenuItem(const DisplayController& display_controller);
};
#endif
