//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t enca_pin, uint8_t encb_pin, uint8_t button_pin, unsigned long debounce_duration)
: enca_pin(enca_pin), encb_pin(encb_pin), button_pin(button_pin), debounce_duration(debounce_duration) {}

void RotaryEncoder::setup(void (*button_input)(), void (*button_pressed)()) {
    this->button_pressed = button_pressed;
    pinMode(enca_pin, INPUT_PULLUP);
    pinMode(encb_pin, INPUT_PULLUP);
    pinMode(button_pin, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(enca_pin), , CHANGE);
    // attachInterrupt(digitalPinToInterrupt(encb_pin), , CHANGE);
    attachInterrupt(digitalPinToInterrupt(button_pin), button_input, RISING);
}

void RotaryEncoder::buttonInput(unsigned long current_time) {
    // Only call button_pressed() after the debounce duration has expired from the last button input.
    if(last_button_press + debounce_duration <= current_time) {
        button_pressed();
        last_button_press = current_time;
    }
}

