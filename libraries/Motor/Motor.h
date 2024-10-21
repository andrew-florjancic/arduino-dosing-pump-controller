//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

// Sends input to a DRV8871 motor driver.
class Motor {
    public:

        /* Constructor creates a Motor.
        * If the motor is only going to be operated in one direction, then only one PWM pin is required for operation.
        * @param in1: A pointer to the Arduino PWM pin connected to the DRV8871 IN1 pin.
        * If the Arduino is not going to use the DRV8871 IN1 pin, then pass in `nullptr` for this parameter.
        * @param in2: A pointer to the Arduino PWM pin connected to the DRV8871 IN2 pin.
        * If the Arduino is not going to use the DRV8871 IN2 pin, then pass in `nullptr` for this parameter.*/
        Motor(uint8_t* in1, uint8_t* in2);

        // Sets up the pinmodes and sets the motor to off.
        void setup();

        // Turns the motor on in the forward direction at the provided PWM duty cycle.
        // @param duty_cycle: The PWM duty cycle that the motor should operate at.
        void forward(uint8_t duty_cycle);

        // Turns the motor on in the reverse direction at the provided PWM duty cycle.
        // @param duty_cycle: The PWM duty cycle that the motor should operate at.
        void reverse(uint8_t duty_cycle);

        // Turns the motor off.
        void off();
    private:
        const uint8_t min_duty_cycle = 0; // Off
        const uint8_t* in1; // A pointer to the Arduino PWM pin connected to the DRV8871 IN1 pin, nullptr if not used.
        const uint8_t* in2; // A pointer to the Arduino PWM pin connected to the DRV8871 IN2 pin, nullptr if not used.
};
#endif
