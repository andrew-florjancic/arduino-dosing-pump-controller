//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Arduino.h>
#include <DoublyLinkedList.h>

// A Rotary Encoder that can recieve and decode input.
class RotaryEncoder {
    public:
        // Input actions that a RotaryEncoder can handle.
        // `left`, `right`, and `select`.
        enum Actions { left, right, select };

        // Constructor creates a RotaryEncoder.
        // @param enc_a: The Arduino Pin# connected to the rotary encoder pin A.
        // @param enc_b: The Arduino Pin# connected to the rotary encoder pin B.
        // @param button: The Arduino Pin# connected to one of the rotary encoder push button switch pins.
        RotaryEncoder(uint8_t enc_a, uint8_t enc_b, uint8_t button, unsigned long debounce_duration);

        // Sets the pinmodes and attaches interrupts.
        // @param a_input: A callback function that will be called every time a change in value for encoder pin A is detected.
        // @param b_input: A callback function that will be called every time a change in value for encoder pin B is detected.
        // @param button_input: A callback function that will be called for every input triggered by the button switch.
        // @param button_pressed: A callback function that will be called for true button press events, debounce is handled in this library.
        void setup(void (*a_input)(), void (*b_input)(), void (*button_input)(), void (*action_detected)(Actions action));

        // This method is called any time physical button is pressed even from an accidental bounce.
        // Debounce handling occurs here and only calls `button_pressed()` if the debounce duration has expired since the last button press.
        void buttonInput(unsigned long current_time);

        // Called every time the Rotary Encoder A value changes. Updates the encoder state based on the current value from the A pin.
        void encodeA();

        // Called every time the Rotary Encoder B value changes. Updates the encoder state based on the current value from the B pin.
        void encodeB();
    private:
        // Rotation states of the encoder.
        enum EncoderState {l3, l2, l1, neutral, r1, r2, r3};

        // Current state of the Rotary Encoder.
        DoublyLinkedList<EncoderState> encoder_state = DoublyLinkedList<EncoderState>();

        const uint8_t enc_a; // The Arduino Pin# connected to the Rotary Encoder ENCA pin.
        const uint8_t enc_b; // The Arduino Pin# connected to the Rotary Encoder ENCB pin.
        const uint8_t button; // The Arduino Pin# connected to one of the Rotary Encoder switch pins.
        void (*action_detected)(Actions action); // Callback function to be called when a button true press event occurs.
        const unsigned long debounce_duration; // Length of time in milliseconds to account for debounce and ignore input.
        unsigned long last_button_press = 0; // The last time the button was pressed.
};
#endif
