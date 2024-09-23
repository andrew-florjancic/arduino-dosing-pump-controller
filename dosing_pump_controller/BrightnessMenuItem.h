//  Created by Andrew Florjancic on 9/22/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef BrightnessMenuItem_h
#define BrightnessMenuItem_h

#include <Arduino.h>
#include <MenuItem.h>
#include "DisplayController.h"

class BrightnessMenuItem : public MenuItem {
    private:
        const DisplayController* display_controller; 
        const String input_message = "Brightness: ";
        void showFeature();
        void presentableWillDismiss();
        void leftAction();
        void rightAction();
        void selectAction();
    public:
        BrightnessMenuItem(DisplayController* display_controller);
};

#endif