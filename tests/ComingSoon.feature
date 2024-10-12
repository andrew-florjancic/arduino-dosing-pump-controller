Feature: Coming Soon
A placeholder menu item for features currently in development

    Background: User is on the Coming Soon screen
        Given the Coming Soon screen is displayed
    
    Scenario: Coming soon message is displayed
        Then the text displayed on the screen is: "Coming soon!"

    Scenario: User returns to the previous Presentable
        When the user presses the select button
        Then the Coming Soon feature is dismissed
        And the user is returned to the previous screen