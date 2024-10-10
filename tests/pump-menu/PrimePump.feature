Feature: Prime Pump

    Scenario: User turns the pump on
        Given the user is viewing the Prime Pump feature on the Start screen
        When the user selects the current operation
        Then the pump is: turned on
        And The Start screen is dismissed
        And the Stop screen is displayed
    
    Scenario: User turns the pump off
        Given the user is viewing the Prime Pump feature on the Stop screen
        When the user selects the current operation
        Then the pump is: turned off
        And The Stop screen is dismissed
        And the Pump Menu is displayed
        