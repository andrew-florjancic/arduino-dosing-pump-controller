Feature: Calibrate Pump

    Scenario Outline: User selects PWM
        Given the user is viewing the Calibrate Pump feature on the PWM selection screen
        And the current PWM is: <pwm>
        When the user turns the rotary encoder to the <direction>
        Then the current PWM is: <new_pwm>

        Scenarios: User turns the rotary encoder to the left
            | pwm | direction |  new_pwm |
            |   0 |      left |        0 |
            |   1 |      left |        0 |
            | 255 |      left |      244 |

        Scenarios: User turns the rotary encoder to the right
            | pwm | direction |  new_pwm |
            |   0 |     right |        1 |
            | 254 |     right |      255 |
            | 255 |     right |      255 |
    
    Scenario: User starts calibration
        Given the user is viewing the Calibrate Pump feature on the PWM selection screen
        When the user selects a PWM value
        Then the PWM selection screen should be dismissed
        And the pump is turned on
        And the Caibrating screen is displayed
        And after 100 seconds has expired the pump is turned off
        And after 100 seconds has expired the Calibrating screen is dismissed
        And after 100 seconds has expired the Calibration Complete screen is displayed

    Scenario: User returns to the pump menu
        Given the user is viewing the Calibrate Pump Feature on the Calibration Complete screen
        When the user presses the select button
        Then the Calibrate Pump feature is dismissed
        And the Pump Menu is displayed
