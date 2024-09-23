//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t enc_a, uint8_t enc_b, uint8_t button, unsigned long debounce_duration)
: enc_a(enc_a), enc_b(enc_b), button(button), debounce_duration(debounce_duration) {}

void RotaryEncoder::setup(void (*a_input)(), void (*b_input)(), void (*button_input)(), void (*action_detected)(Actions action)) {
    this->action_detected = action_detected;
    // Append all encoder states to the encoder_state list.
    encoder_state.append(l3); encoder_state.append(l2); encoder_state.append(l1);
    encoder_state.append(neutral);
    encoder_state.append(r1); encoder_state.append(r2); encoder_state.append(r3);
    
    encoder_state.setCurrentItem(neutral); // The Rotary Encoder should be in the neutral position during setup.
    
    // Transform the encoder_state DLL into the Doubly Half-Circular Linked List State Machine abomination. 
    // l3's previous node and r3's next node is the neutral node in the middle of the list.
    // See RotaryEncoderStateMachineDiagram.svg for more details.
    DLLNode<EncoderState>* current = encoder_state.getCurrentItem();
    encoder_state.getHead()->previous_node = current;
    encoder_state.getTail()->next_node = current;
    
    // Set pinmodes and attach interrupts.
    pinMode(enc_a, INPUT_PULLUP);
    pinMode(enc_b, INPUT_PULLUP);
    pinMode(button, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(enc_a), a_input, CHANGE);
    attachInterrupt(digitalPinToInterrupt(enc_b), b_input, CHANGE);
    attachInterrupt(digitalPinToInterrupt(button), button_input, RISING);
}

void RotaryEncoder::buttonInput(unsigned long current_time) {
    // Only call action_detected() after the debounce duration has expired from the last button input.
    if(last_button_press + debounce_duration <= current_time) {
        action_detected(select);
        last_button_press = current_time;
    }
}

void RotaryEncoder::encodeA() {
    uint8_t a_value = digitalRead(enc_a);
    switch(encoder_state.getCurrentItem()->data) {
        case l3:
            if(a_value == 1) {
                 // Left rotation complete, Advance to Neutral.
                encoder_state.previousItem();
                action_detected(left);
            }
            break;
        case l2:
            if(a_value == 1) {
                encoder_state.nextItem(); // Return to L1.
            }
            break;
        case l1:
            if(a_value == 0) {
                encoder_state.previousItem(); // Advance to L2.
            }
            break;
        case neutral:
            if(a_value == 0) {
                encoder_state.nextItem(); // Advance to R1.
            }
            break;
        case r1:
            if(a_value == 1) {
                encoder_state.previousItem(); // Return to Neutral.
            }
            break;
        case r2:
            if(a_value == 1) {
                encoder_state.nextItem(); // Advance to R3.
            }
            break;
        case r3:
            if(a_value == 0) {
                encoder_state.previousItem(); // Return to R2.
            }
            break;
    }
}

void RotaryEncoder::encodeB() {
    uint8_t b_value = digitalRead(enc_b);
    switch(encoder_state.getCurrentItem()->data) {
        case l3:
            if(b_value == 0) {
                encoder_state.nextItem(); // Return to L2.
            }
            break;
        case l2:
            if(b_value == 1) {
                encoder_state.previousItem(); // Advance to L3.
            }
            break;
        case l1:
            if(b_value == 1) {
                encoder_state.nextItem(); // Return to Neutral.
            }
            break;
        case neutral:
            if(b_value == 0) {
                encoder_state.previousItem(); // Advance to L1.
            }
            break;
        case r1:
            if(b_value == 0) {
                encoder_state.nextItem(); // Advance to R2.
            }
            break;
        case r2:
            if(b_value == 1) {
                encoder_state.previousItem(); // Return to R1.
            }
            break;
        case r3:
            if(b_value == 1) {
                // Right rotation complete, Advance to Neutral.
                encoder_state.nextItem();
                action_detected(right);
            }
            break;
    }
}
