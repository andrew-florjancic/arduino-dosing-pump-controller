//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "Motor.h"

Motor::Motor(uint8_t* in1, uint8_t* in2) : in1(in1), in2(in2) { }

void Motor::setup() {
    if(in1 != nullptr) { pinMode(*in1, OUTPUT); }
    if(in2 != nullptr) { pinMode(*in2, OUTPUT); }
    off();
}

void Motor::forward(uint8_t duty_cycle) {
    if(in1 != nullptr) { analogWrite(*in1, min_duty_cycle); }
    if(in2 != nullptr) { analogWrite(*in2, duty_cycle); }
}

void Motor::reverse(uint8_t duty_cycle) {
    if(in1 != nullptr) { analogWrite(*in1, duty_cycle); }
    if(in2 != nullptr) { analogWrite(*in2, min_duty_cycle); }
}

void Motor::off() {
    if(in1 != nullptr) { analogWrite(*in1, min_duty_cycle); }
    if(in2 != nullptr) { analogWrite(*in2, min_duty_cycle); }
}
