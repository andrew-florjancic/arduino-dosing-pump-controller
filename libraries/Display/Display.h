//  Created by Andrew Florjancic on 9/17/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef Display_h
#define Display_h

#include <Arduino.h>
#include <LiquidCrystal.h>

// User interface component to interact with a LCD screen.
class Display {
    public:
        const uint8_t rows = 2; // Number of rows on the LCD.
        const uint8_t columns = 16; // Number of columns on the LCD.
        const LiquidCrystal lcd; // The LiquidCrystal object used to interface with the LCD.

        /*
        * Constructor that creates a new Display object.
        * 
        * @param lcd: The LiquidCrystal object used to display information.
        * @param rows: The number of rows on the LCD.
        * @param columns: The number of columns on the LCD.
        * @param backlight_pin: A pointer to the Arduino PWM pin# that is connected to the LCD backlight pin.
        * If the Arduino is not going to control the LCD backlight, then pass in `nullptr` for this parameter.
        * @param contrast_pin: A pointer to the Arduino PWM pin# that is connected to the LCD contrast pin.
        * If the Arduino is not going to control the LCD contrast, then pass in `nullptr` for this parameter.
        */ 
        Display(const LiquidCrystal lcd, uint8_t rows, uint8_t columns, uint8_t* backlight_pin, uint8_t* contrast_pin);

        // Sets the pinmodes for the backlight and contrast pins then initializes the LCD screen.
        void setup();

        // Sets the duty cycle that power is supplied to the backlight pin of the LCD.
        // @param duty_cycle: The PWM duty cycle that the backlight pin should be supplied power.
        void setBrightness(uint8_t duty_cycle);

        // Sets the duty cycle that power is supplied to the contrast pin of the LCD.
        // @param duty_cycle: The PWM duty cycle that the contrast pin should be supplied power.
        void setContrast(uint8_t duty_cycle);
    private:
        const uint8_t* backlight_pin; // A pointer to the Arduino pin number connected to the LCD backlight pin or nullptr if not used.
        const uint8_t* contrast_pin; // A pointer to the Arduino pin number connected to the LCD contrast pin or nullptr if not used.
};

#endif
