//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Arduino.h>

// A Rotary Encoder that can recieve and decode input.
class RotaryEncoder {
    public:
        // Input actions that a RotaryEncoder can handle.
        // `left`, `right`, and `select`.
        enum Actions { left, right, select };

        // Constructor creates a RotaryEncoder.
        // @param enca_pin: The Arduino Pin# connected to the rotary encoder ENCA pin.
        // @param encb_pin: The Arduino Pin# connected to the rotary encoder ENCB pin.
        // @param button_pin: The Arduino Pin# connected to one of the rotary encoder push button switch pins.
        RotaryEncoder(uint8_t enca_pin, uint8_t encb_pin, uint8_t button_pin, unsigned long debounce_duration);

        // Sets the pinmodes and attaches interrupts.
        // @param button_input: A callback function that will be called for every input triggered by the button switch.
        // @param button_pressed: A callback function that will be called for true button press events, debounce is handled in this library.
        void setup(void (*button_input)(), void (*action_detected)(Actions action));

        // This method is called any time physical button is pressed even from an accidental bounce.
        // Debounce handling occurs here and only calls `button_pressed()` if the debounce duration has expired since the last button press.
        void buttonInput(unsigned long current_time);
    private:
        const uint8_t enca_pin; // The Arduino Pin# connected to the Rotary Encoder ENCA pin.
        const uint8_t encb_pin; // The Arduino Pin# connected to the Rotary Encoder ENCB pin.
        const uint8_t button_pin; // The Arduino Pin# connected to one of the Rotary Encoder switch pins.
        void (*action_detected)(Actions action); // Callback function to be called when a button true press event occurs.
        const unsigned long debounce_duration; // Length of time in milliseconds to account for debounce and ignore input.
        unsigned long last_button_press = 0; // The last time the button was pressed.
};
#endif