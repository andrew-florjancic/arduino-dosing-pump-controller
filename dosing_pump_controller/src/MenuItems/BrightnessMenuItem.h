//  Created by Andrew Florjancic on 9/22/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef BrightnessMenuItem_h
#define BrightnessMenuItem_h

#include <Arduino.h>
#include <MenuItem.h>
#include "../Controllers/DisplayController.h"

// A Menu item that allows the user to adjust and save the brightness setting.
class BrightnessMenuItem : public MenuItem {
    private:
        // The DisplayController used to update and save brightness settings.
        DisplayController display_controller;

        // The message displayed to the user when selecting a brightness value.
        const String input_message = "Brightness: ";

        // Displays the current brightness level to the user.
        void showFeature();
        
        // Decrements the brightness level.
        void leftAction() override;

        // Increments the brightness level.
        void rightAction() override;

        // Saves the current brightness level to stored device settings.
        void selectAction();
    public:

        // Constructor creates a BrightnessMenuItem.
        // @param display_controller: The DisplayController that will be used to update and save brightness settings.
        BrightnessMenuItem(DisplayController& display_controller);
};
#endif
