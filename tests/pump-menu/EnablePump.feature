Feature: Enable Pump

    Scenario Outline: User updates pump status
        Given the user is viewing the Enable Pump feature
        And the current pump status is: <current_status>
        When the user turns the rotary encoder to the <direction>
        Then the current pump status is: <new_status>

        Scenarios: User turns the rotary encoder to the left
            | current_status | direction |  new_status |
            |            Off |      left |         Off |
            |             On |      left |         Off |

        Scenarios: User turns the rotary encoder to the right
            | current_status | direction |  new_status |
            |            Off |     right |          On |
            |             On |     right |          On |

    Scenario: User selects current pump status
    Given the user is viewing the Enable Pump feature
    When the user selects the current pump status
    Then the Enablke Pump feature is dismissed
    And the pump menu is displayed
