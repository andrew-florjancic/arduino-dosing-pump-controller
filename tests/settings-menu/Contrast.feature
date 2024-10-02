Feature: LCD Contrast feature

    Background: User is on the Contrast screen
        Given the Contrast screen is displayed

    Scenario Outline: User changes the contrast setting
        Given the current contrast value displayed is: <current_value>
        When the user rotates the rotary encoder to the <direction>
        Then the current contrast value displayed is: <new_value>
        And the contrast of the LCD screen is <equality> the previous setting

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
            |            50 |     right |         50 |        = |

    Scenario: User saves contrast setting and is returned to the settings menu
        When the user presses the rotary encoder button
        Then the contrast screen is dismissed
        And the settings screen is displayed

    Scenario Outline: User saved contrast setting and the setting persists after device restart
        Given the user saved a contrast setting
        When the user restarts the device
        And navigates to the contrast screen
        Then the current contrast value displayed is: <value>
    
        Scenarios: The saved contrast setting value
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
