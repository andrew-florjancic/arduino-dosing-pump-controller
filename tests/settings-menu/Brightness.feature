Feature: LCD Brightness feature

    Background: User is on the Brightness screen
        Given the Brightness screen is displayed

    Scenario Outline: User changes the brightness setting
        Given the current Brightness value displayed is: <current_value>
        When the user rotates the rotary encoder to the <direction>
        Then the current Brightness value displayed is: <new_value>
        And the brightness of the LCD screen is <brightness>

        Scenarios: User turns the rotary encoder to the left
            | current_value | direction | new_value  | brightness |
            |             0 |      left |          0 |   the same |
            |             5 |      left |          0 |     darker |
            |            10 |      left |          5 |     darker |
            |            15 |      left |         10 |     darker |
            |            20 |      left |         15 |     darker |
            |            25 |      left |         20 |     darker |
            |            30 |      left |         25 |     darker |
            |            35 |      left |         30 |     darker |
            |            40 |      left |         35 |     darker |
            |            45 |      left |         40 |     darker |
            |            50 |      left |         45 |     darker |
            |            55 |      left |         50 |     darker |
            |            60 |      left |         55 |     darker |
            |            65 |      left |         60 |     darker |
            |            70 |      left |         65 |     darker |
            |            75 |      left |         70 |     darker |
            |            80 |      left |         75 |     darker |
            |            85 |      left |         80 |     darker |
            |            90 |      left |         85 |     darker |
            |            95 |      left |         90 |     darker |
            |           100 |      left |         95 |     darker |
    
        Scenarios: User turns the rotary encoder to the right
            | current_value | direction | new_value  | brightness |
            |             0 |     right |          5 |   brighter |
            |             5 |     right |         10 |   brighter |
            |            10 |     right |         15 |   brighter |
            |            15 |     right |         20 |   brighter |
            |            20 |     right |         25 |   brighter |
            |            25 |     right |         30 |   brighter |
            |            30 |     right |         35 |   brighter |
            |            35 |     right |         40 |   brighter |
            |            40 |     right |         45 |   brighter |
            |            45 |     right |         50 |   brighter |
            |            50 |     right |         55 |   brighter |
            |            55 |     right |         60 |   brighter |
            |            60 |     right |         65 |   brighter |
            |            65 |     right |         70 |   brighter |
            |            70 |     right |         75 |   brighter |
            |            75 |     right |         80 |   brighter |
            |            80 |     right |         85 |   brighter |
            |            85 |     right |         90 |   brighter |
            |            90 |     right |         95 |   brighter |
            |            95 |     right |        100 |   brighter |
            |           100 |     right |        100 |   the same |


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
