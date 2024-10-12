Feature: Settings Menu feature
    Background: User is viewing the settings menu
        Given the user is on the settings menu

    Scenario Outline: User navigates the settings menu
        And the first menu item displayed is: <initial_first>
        And the second menu item displayed is: <initial_second>
        When the user rotates the rotary encoder to the <direction>
        Then the first menu item displayed is: <updated_first>
        And the second menu item displayed is: <updated_second>

        Scenarios: User turns the rotary encoder to the left
            | initial_first | initial_second | direction | updated_first | updated_second |
            |        Return |     Brightness |      left |        Return |     Brightness |
            |    Brightness |       Contrast |      left |        Return |     Brightness |
            |      Contrast |       Set Time |      left |    Brightness |       Contrast |
            |      Set Time |      Reset All |      left |      Contrast |       Set Time |
            |     Reset All |           None |      left |      Set Time |      Reset All |
    
        Scenarios: User turns the rotary encoder to the right
            | initial_first | initial_second | direction | updated_first | updated_second |
            |        Return |     Brightness |     right |    Brightness |       Contrast |
            |    Brightness |       Contrast |     right |    Contrast   |       Set Time |
            |      Contrast |       Contrast |     right |    Set Time   |      Reset All |
            |      Set Time |      Reset All |     right |    Reset All  |           None |
            |     Reset All |           None |     right |    Reset All  |           None |

    Scenario Outline: User selects the current item
        When the user selects the <current_item>
        Then the settings menu will no longer be displayed
        And the <feature> will be displayed

        Scenarios:
            | current_item |         feature |
            |       Return |       Main Menu |
            |   Brightness |      Brightness |
            |     Contrast |        Contrast |
            |     Set Time | Set Date & Time |
            |    Reset All |   Factory Reset |
            