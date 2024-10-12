Feature: Pump Menu feature
    Background: User is viewing a Pump Menu
        Given the user is a Pump Menu

    Scenario Outline: User navigates a Pump Menu
        And the first menu item displayed is: <initial_first>
        And the second menu item displayed is: <initial_second>
        When the user rotates the rotary encoder to the <direction>
        Then the first menu item displayed is: <updated_first>
        And the second menu item displayed is: <updated_second>

        Scenarios: User turns the rotary encoder to the left
            | initial_first | initial_second | direction | updated_first | updated_second |
            |        Return |       Set Dose |      left |        Return |       Set Dose |
            |      Set Dose |    Enable Pump |      left |        Return |       Set Dose |
            |   Enable Pump |          Prime |      left |      Set Dose |    Enable Pump |
            |         Prime |      Calibrate |      left |   Enable Pump |          Prime |
            |     Calibrate |          Reset |      left |         Prime |      Calibrate |
            |         Reset |           None |      left |     Calibrate |          Reset |
    
        Scenarios: User turns the rotary encoder to the right
            | initial_first | initial_second | direction | updated_first | updated_second |
            |        Return |       Set Dose |     right |      Set Dose |    Enable Pump |
            |      Set Dose |    Enable Pump |     right |   Enable Pump |          Prime |
            |   Enable Pump |          Prime |     right |         Prime |      Calibrate |
            |         Prime |      Calibrate |     right |     Calibrate |          Reset |
            |     Calibrate |          Reset |     right |         Reset |           None |
            |         Reset |           None |     right |         Reset |           None |

    Scenario Outline: User selects the current item
        When the user selects the <current_item>
        Then the settings menu will no longer be displayed
        And the <feature> will be displayed
        
        Scenarios:
            | current_item |        feature |
            |       Return |      Main Menu |
            |     Set Dose |       Set Dose |
            |  Enable Pump |    Enable Pump |
            |        Prime |     Prime Pump |
            |    Calibrate | Calibrate Pump |
            |        Reset |     Reset Pump |
        