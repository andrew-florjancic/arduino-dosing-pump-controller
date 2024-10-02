Feature: LCD Brightness feature

    Background: User is on the Brightness screen
        Given the Brightness screen is displayed

    Scenario Outline: User changes the brightness setting
        Given the current Brightness value displayed is: <current_value>
        When the user rotates the rotary encoder to the <direction>
        Then the current Brightness value displayed is: <new_value>
        And the brightness of the LCD screen is <equality> the previous setting

        Scenarios: User turns the rotary encoder to the left
            | current_value | direction | new_value  | equality |
            |             0 |      left |          0 |        = |
            |             5 |      left |          0 |        < |
            |            10 |      left |          5 |        < |
            |            15 |      left |         10 |        < |
            |            20 |      left |         15 |        < |
            |            25 |      left |         20 |        < |
            |            30 |      left |         25 |        < |
            |            35 |      left |         30 |        < |
            |            40 |      left |         35 |        < |
            |            45 |      left |         40 |        < |
            |            50 |      left |         45 |        < |
            |            55 |      left |         50 |        < |
            |            60 |      left |         55 |        < |
            |            65 |      left |         60 |        < |
            |            70 |      left |         65 |        < |
            |            75 |      left |         70 |        < |
            |            80 |      left |         75 |        < |
            |            85 |      left |         80 |        < |
            |            90 |      left |         85 |        < |
            |            95 |      left |         90 |        < |
            |           100 |      left |         95 |        < |
    
        Scenarios: User turns the rotary encoder to the right
            | current_value | direction | new_value  | equality |
            |             0 |     right |          5 |        > |
            |             5 |     right |         10 |        > |
            |            10 |     right |         15 |        > |
            |            15 |     right |         20 |        > |
            |            20 |     right |         25 |        > |
            |            25 |     right |         30 |        > |
            |            30 |     right |         35 |        > |
            |            35 |     right |         40 |        > |
            |            40 |     right |         45 |        > |
            |            45 |     right |         50 |        > |
            |            50 |     right |         55 |        > |
            |            55 |     right |         60 |        > |
            |            60 |     right |         65 |        > |
            |            65 |     right |         70 |        > |
            |            70 |     right |         75 |        > |
            |            75 |     right |         80 |        > |
            |            80 |     right |         85 |        > |
            |            85 |     right |         90 |        > |
            |            90 |     right |         95 |        > |
            |            95 |     right |        100 |        > |
            |           100 |     right |        100 |        = |


    Scenario: User saves brightness setting and is returned to the settings menu
        When the user presses the rotary encoder button
        Then the brightenss screen is dismissed
        And the settings screen is displayed

    Scenario Outline: User saved brightness setting and the setting persists after device restart
        Given the user saved a brightness setting
        When the user restarts the device
        And navigates to the brightness screen
        Then the current Brightness value displayed is: <value>
    
        Scenarios: The saved brightness setting value
            | value |
            |     0 |
            |     5 |
            |    10 |
            |    15 |
            |    20 |
            |    25 |
            |    30 |
            |    35 |
            |    40 |
            |    45 |
            |    50 |
            |    55 |
            |    60 |
            |    65 |
            |    70 |
            |    75 |
            |    80 |
            |    85 |
            |    90 |
            |    95 |
            |   100 |
