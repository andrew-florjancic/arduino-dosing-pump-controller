Feature: Main Menu 
    Background: User is viewing the Main Menu
        Given the user is on the Main Menu

    Scenario Outline: User navigates a the Main Menu
        Given the first menu item displayed is: <initial_first>
        And the second menu item displayed is: <initial_second>
        When the user rotates the rotary encoder to the <direction>
        Then the first menu item displayed is: <updated_first>
        And the second menu item displayed is: <updated_second>

        Scenarios: User turns the rotary encoder to the left
            | initial_first | initial_second | direction | updated_first | updated_second |
            |  Start Dosing |         Pump 1 |      left |  Start Dosing |         Pump 1 |
            |        Pump 1 |         Pump 2 |      left |  Start Dosing |         Pump 1 |
            |        Pump 2 |         Pump 3 |      left |        Pump 1 |         Pump 2 |
            |        Pump 3 |       Settings |      left |        Pump 2 |         Pump 3 |
            |      Settings |           None |      left |        Pump 3 |       Settings |
    
        Scenarios: User turns the rotary encoder to the right
            | initial_first | initial_second | direction | updated_first | updated_second |
            |  Start Dosing |         Pump 1 |     right |        Pump 1 |         Pump 2 |
            |        Pump 1 |         Pump 2 |     right |        Pump 2 |         Pump 3 |
            |        Pump 2 |         Pump 3 |     right |        Pump 3 |       Settings |
            |        Pump 3 |       Settings |     right |      Settings |           None |
            |      Settings |           None |     right |      Settings |           None |

    Scenario Outline: User selects the current item
        When the user selects the <current_item>
        Then the Main Menu is dismissed
        And the <feature> is displayed
        | current_item |       feature |
        | Start Dosing |        Dosing |
        |       Pump 1 |   Pump 1 Menu |
        |       Pump 2 |   Pump 2 Menu |
        |       Pump 3 |   Pump 3 Menu |
        |     Settings | Settings Menu |
