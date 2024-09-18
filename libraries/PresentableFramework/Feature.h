//  Created by Andrew Florjancic on 9/17/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef Feature_h
#define Feature_h

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Display.h>

// A Feature that can show content to the user.
class Feature {
    public:
        // Constructor creates a new feature.
        Feature();
    protected:
        // The Display object used to show Feature content to the user.
        Display display;

        // Displays the feature.
        virtual void showFeature() = 0;

        // Displays an error message with an error code.
        // @param code: The error code to display.
        void showError(uint8_t code);
    private:
        // Error message to be displayed alerting the user an error has occured.
        const String error_message = "Error!";
        const String error_code_message = "Code: ";
};

#endif