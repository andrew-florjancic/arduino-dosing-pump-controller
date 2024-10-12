Feature: Dosing 
    Background: User is viewing the Dosing feature
        Given the user is on the Dosing screen

    Scenario: User stops dosing and returns to the main menu
        When the user presses the select button
        Then the Dosing feature is dismissed
        And the Main Menu is displayed
        And all enabled dosing pumps stop dosing
    
    Scenario Outline: Dosing Schedule
        Given <pump#>'s enabled status is: <enabled>
        Then the <pump#> on the screen displays: <enabled>

        Scenarios: Testing Pump 1 Dosing schedules
        |  pump# | enabled |
        | Pump 1 |     Off |
        | Pump 1 |      On |
        | Pump 2 |     Off |
        | Pump 2 |      On |
        | Pump 3 |     Off |
        | Pump 3 |      On |
