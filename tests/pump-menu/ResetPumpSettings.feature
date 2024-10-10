Feature: Reset Pump Settings

    Scenario Outline: User updates confirmation prompt
        Given the user is viewing the Reset Pump Settings feature
        And the current confirmation status is: <current_confirmation>
        When the user turns the rotary encoder to the <direction>
        Then the current confirmation status is: <new_confirmation>

        Scenarios: User turns the rotary encoder to the left
            | current_confirmation | direction |  new_confirmation |
            |               Cancel |      left |            Cancel |
            |                Reset |      left |            Cancel |

        Scenarios: User turns the rotary encoder to the right
            | current_confirmation | direction |  new_confirmation |
            |               Cancel |     right |             Reset |
            |                Reset |     right |             Reset |
    
    Scenario Outline: User selects cancel/reset and returns to the pump menu
        Given the user is viewing the Reset Pump Settings feature
        And the current confirmation status is: <confirmation>
        When the user selects the current operation
        Then the Reset Pump feature is dismissed
        And the pump menu is displayed

        Scenarios:
        | confirmation |
        |       Cancel |
        |        Reset |
        