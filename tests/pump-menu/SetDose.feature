Feature: Set Dose feature

    Scenario Outline: User navigates a Pump Menu
        Given the user is viewing the Doses Per Day input section of the Set Dose feature
        And the current doses/day displayed is: <initial_doses>
        When the user rotates the rotary encoder to the <direction>
        Then the current doses/day displayed is: <updated_doses>

        Scenarios: User turns the rotary encoder to the left
            | initial_doses | direction | updated_doses |
            |             2 |      left |             2 |
            |             3 |      left |             2 |
            |             4 |      left |             3 |
            |             6 |      left |             4 |
            |             8 |      left |             6 |
            |            12 |      left |             8 |
            |            24 |      left |            12 |
            |            48 |      left |            24 |
            |            96 |      left |            48 |
            |           192 |      left |            96 |

    
        Scenarios: User turns the rotary encoder to the right
            | initial_doses | direction | updated_doses |
            |             2 |     right |             3 |
            |             3 |     right |             4 |
            |             4 |     right |             6 |
            |             6 |     right |             8 |
            |             8 |     right |            12 |
            |            12 |     right |            24 |
            |            24 |     right |            48 |
            |            48 |     right |            96 |
            |            96 |     right |           192 |
            |           192 |     right |           192 |

    Scenario: User selects doses per day
        Given the user is viewing the Doses Per Day input section of the Set Dose feature
        When the user selects an option
        Then the Doses Per day section should no longer be displayed
        And the Set Dose Quantity section should be displayed
    
    Scenario Outline: User selects Set Dose quantity
        Given the user is viewing the Set Dose Day input section of the Set Dose feature
        And the user is on the modify <initial section> section
        When the user selects the current dose
        Then the Set Dose <initial_section> is dismissed
        And the Set Dose <new_section> is displayed

        Scenarios:
        | initial_section | new_section |
        |  hundreds input |  tens input |
        |      tens input |  ones input |
        |      ones input |   Doses Set |

    Scenario: User returns to the Pump Menu
        Given the user is viewing the Set Dose feature on the Doses Set section
        And the user presses the select input button
        Then the Set Doses feature is dismissed
        And the Pump Menu is displayed

    # Intentionally omitting non-egde cases because it would be a major pain to verify with manual testing, we can consider adding them if automated tests are created in the future
    # This is also relatively low risk straight forward decrement operation, if the edge cases are working fine then everything else should also be fine.
    Scenario Outline: User updates dose quantity
        Given the user is viewing the dose quantity section
        And is adjusting the <position> place value
        And the doses per day selected was: <doses>
        And the current dose is: <dose>
        When the user rotates the rotary encoder to the <direction>
        Then the current dose is <updated_dose>

        Scenarios: User turn the rotary encoder to the left when modifying the hundreds place
            | doses | position |  dose | direction | updated_dose |
            |     2 | hundreds |     0 |      left |            0 |
            |     2 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-43100 if/when automated tests are created
            |     2 | hundreds | 43200 |      left |        43100 |
            |     3 | hundreds |     0 |      left |            0 |
            |     3 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-28700 if/when automated tests are created
            |     3 | hundreds | 28800 |      left |        28700 |
            |     4 | hundreds |     0 |      left |            0 |
            |     4 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-2150 if/when automated tests are created
            |     4 | hundreds | 21600 |      left |        21500 |
            |     6 | hundreds |     0 |      left |            0 |
            |     6 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-14300 if/when automated tests are created
            |     6 | hundreds | 14440 |      left |        14300 |
            |     8 | hundreds |     0 |      left |            0 |
            |     8 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-10700 if/when automated tests are created
            |     8 | hundreds | 10800 |      left |        10700 |
            |    12 | hundreds |     0 |      left |            0 |
            |    12 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-7100 if/when automated tests are created
            |    12 | hundreds |  7200 |      left |         7100 |
            |    24 | hundreds |     0 |      left |            0 |
            |    24 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-3500 if/when automated tests are created
            |    24 | hundreds |  3600 |      left |         3500 |
            |    48 | hundreds |     0 |      left |            0 |
            |    48 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-1700 if/when automated tests are created
            |    48 | hundreds |  1800 |      left |         1700 |
            |    96 | hundreds |     0 |      left |            0 |
            |    96 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-800 if/when automated tests are created
            |    96 | hundreds |   900 |      left |          800 |
            |   192 | hundreds |     0 |      left |            0 |
            |   192 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-400 if/when automated tests are created
            |   192 | hundreds |   500 |      left |          400 |

        Scenarios: User turns the rotary encoder to the left when modifying the tens place
            | doses | position |  dose | direction | updated_dose |
            |     2 |     tens |     0 |      left |            0 |
            |     2 |     tens |    10 |      left |            0 |
            # TODO: Add 20-43190 if/when automated tests are created
            |     2 |     tens | 43200 |      left |        43190 |
            |     3 |     tens |     0 |      left |            0 |
            |     3 |     tens |    10 |      left |            0 |
            # TODO: Add 20-28790 if/when automated tests are created
            |     3 |     tens | 28800 |      left |        28790 |
            |     4 |     tens |     0 |      left |            0 |
            |     4 |     tens |    10 |      left |            0 |
            # TODO: Add 200-21590 if/when automated tests are created
            |     4 |     tens | 21600 |      left |        21590 |
            |     6 |     tens |     0 |      left |            0 |
            |     6 |     tens |    10 |      left |            0 |
            # TODO: Add 200-14390 if/when automated tests are created
            |     6 |     tens | 14440 |      left |        14390 |
            |     8 |     tens |     0 |      left |            0 |
            |     8 |     tens |    10 |      left |            0 |
            # TODO: Add 200-10790 if/when automated tests are created
            |     8 |     tens | 10800 |      left |        10790 |
            |    12 |     tens |     0 |      left |            0 |
            |    12 |     tens |    10 |      left |            0 |
            # TODO: Add 200-7190 if/when automated tests are created
            |    12 |     tens |  7200 |      left |         7190 |
            |    24 |     tens |     0 |      left |            0 |
            |    24 |     tens |    10 |      left |            0 |
            # TODO: Add 200-3590 if/when automated tests are created
            |    24 |     tens |  3600 |      left |         3590 |
            |    48 |     tens |     0 |      left |            0 |
            |    48 |     tens |    10 |      left |            0 |
            # TODO: Add 200-1790 if/when automated tests are created
            |    48 |     tens |  1800 |      left |         1790 |
            |    96 |     tens |     0 |      left |            0 |
            |    96 |     tens |    10 |      left |            0 |
            # TODO: Add 200-890 if/when automated tests are created
            |    96 |     tens |   900 |      left |          890 |
            |   192 |     tens |     0 |      left |            0 |
            |   192 |     tens |    10 |      left |            0 |
            # TODO: Add 200-490 if/when automated tests are created
            |   192 |     tens |   500 |      left |          490 |

        Scenarios: User turns the rotary encoder to the left when modifying the ones place
            | doses | position |  dose | direction | updated_dose |
            |     2 |     ones |     0 |      left |            0 |
            |     2 |     ones |     1 |      left |            0 |
            # TODO: Add 20-43199 if/when automated tests are created
            |     2 |     ones | 43200 |      left |        43199 |
            |     3 |     ones |     0 |      left |            0 |
            |     3 |     ones |     1 |      left |            0 |
            # TODO: Add 20-28799 if/when automated tests are created
            |     3 |     ones | 28800 |      left |        28799 |
            |     4 |     ones |     0 |      left |            0 |
            |     4 |     ones |     1 |      left |            0 |
            # TODO: Add 200-21599 if/when automated tests are created
            |     4 |     ones | 21600 |      left |        21590 |
            |     6 |     ones |     0 |      left |            0 |
            |     6 |     ones |     1 |      left |            0 |
            # TODO: Add 200-14399 if/when automated tests are created
            |     6 |     ones | 14440 |      left |        14399 |
            |     8 |     ones |     0 |      left |            0 |
            |     8 |     ones |     1 |      left |            0 |
            # TODO: Add 200-10799 if/when automated tests are created
            |     8 |     ones | 10800 |      left |        10799 |
            |    12 |     ones |     0 |      left |            0 |
            |    12 |     ones |     1 |      left |            0 |
            # TODO: Add 200-7199 if/when automated tests are created
            |    12 |     ones |  7200 |      left |         7199 |
            |    24 |     ones |     0 |      left |            0 |
            |    24 |     ones |     1 |      left |            0 |
            # TODO: Add 200-3599 if/when automated tests are created
            |    24 |     ones |  3600 |      left |         3599 |
            |    48 |     ones |     0 |      left |            0 |
            |    48 |     ones |     1 |      left |            0 |
            # TODO: Add 200-1799 if/when automated tests are created
            |    48 |     ones |  1800 |      left |         1799 |
            |    96 |     ones |     0 |      left |            0 |
            |    96 |     ones |     1 |      left |            0 |
            # TODO: Add 200-899 if/when automated tests are created
            |    96 |     ones |   900 |      left |          899 |
            |   192 |     ones |     0 |      left |            0 |
            |   192 |     ones |     1 |      left |            0 |
            # TODO: Add 200-499 if/when automated tests are created
            |   192 |     ones |   500 |      left |          499 |

        Scenarios: User turn the rotary encoder to the right when modifying the hundreds place
            | doses | position |  dose | direction | updated_dose |
            |     2 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-43000 if/when automated tests are created
            |     2 | hundreds | 43100 |     right |        43200 |
            |     2 | hundreds | 43200 |     right |        43200 |
            |     3 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-28600 if/when automated tests are created
            |     3 | hundreds | 28700 |     right |        28800 |
            |     3 | hundreds | 28800 |     right |        28800 |
            |     4 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-21400 if/when automated tests are created
            |     4 | hundreds | 21500 |     right |        21600 |
            |     4 | hundreds | 21600 |     right |        21600 |
            |     6 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-14200 if/when automated tests are created
            |     6 | hundreds | 14300 |     right |        14400 |
            |     6 | hundreds | 14400 |     right |        14400 |
            |     8 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-10600 if/when automated tests are created
            |     8 | hundreds | 10700 |     right |        10800 |
            |     8 | hundreds | 10800 |     right |        10800 |
            |    12 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-7000 if/when automated tests are created
            |    12 | hundreds |  7100 |     right |         7200 |
            |    12 | hundreds |  7200 |     right |         7200 |
            |    24 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-3400 if/when automated tests are created
            |    24 | hundreds |  3500 |     right |         3600 |
            |    24 | hundreds |  3600 |     right |         3600 |
            |    48 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-1600 if/when automated tests are created
            |    48 | hundreds |  1700 |     right |         1800 |
            |    48 | hundreds |  1800 |     right |         1800 |
            |    96 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-700 if/when automated tests are created
            |    96 | hundreds |   800 |     right |          900 |
            |    96 | hundreds |   900 |     right |          900 |
            |   192 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-300 if/when automated tests are created
            |   192 | hundreds |   400 |     right |          500 |
            |   192 | hundreds |   500 |     right |          500 |

        Scenarios: User turns the rotary encoder to the right when modifying the tens place
            | doses | position |  dose | direction | updated_dose |
            |     2 |     tens |     0 |     right |           10 |
            # TODO: Add 10-43180 if/when automated tests are created
            |     2 |     tens | 43190 |     right |        43200 |
            |     2 |     tens | 43200 |     right |        43200 |
            |     3 |     tens |     0 |     right |           10 |
            # TODO: Add 10-28780 if/when automated tests are created
            |     3 |     tens | 28790 |     right |        28800 |
            |     3 |     tens | 28800 |     right |        28800 |
            |     4 |     tens |     0 |     right |           10 |
            # TODO: Add 10-21580 if/when automated tests are created
            |     4 |     tens | 21590 |     right |        21600 |
            |     4 |     tens | 21600 |     right |        21600 |
            |     6 |     tens |     0 |     right |           10 |
            # TODO: Add 10-14380 if/when automated tests are created
            |     6 |     tens | 14390 |     right |        14400 |
            |     6 |     tens | 14400 |     right |        14400 |
            |     8 |     tens |     0 |     right |           10 |
            # TODO: Add 10-10780 if/when automated tests are created
            |     8 |     tens | 10790 |     right |        10800 |
            |     8 |     tens | 10800 |     right |        10800 |
            |    12 |     tens |     0 |     right |           10 |
            # TODO: Add 10-7180 if/when automated tests are created
            |    12 |     tens |  7190 |     right |         7200 |
            |    12 |     tens |  7200 |     right |         7200 |
            |    24 |     tens |     0 |     right |           10 |
            # TODO: Add 10-3580 if/when automated tests are created
            |    24 |     tens |  3590 |     right |         3600 |
            |    24 |     tens |  3600 |     right |         3600 |
            |    48 |     tens |     0 |     right |           10 |
            # TODO: Add 10-1780 if/when automated tests are created
            |    48 |     tens |  1790 |     right |         1800 |
            |    48 |     tens |  1800 |     right |         1800 |
            |    96 |     tens |     0 |     right |           10 |
            # TODO: Add 10-880 if/when automated tests are created
            |    96 |     tens |   890 |     right |          900 |
            |    96 |     tens |   900 |     right |          900 |
            |   192 |     tens |     0 |     right |           10 |
            # TODO: Add 10-480 if/when automated tests are created
            |   192 |     tens |   490 |     right |          500 |
            |   192 |     tens |   500 |     right |          500 |

        Scenarios: User turns the rotary encoder to the right when modifying the ones place
            | doses | position |  dose | direction | updated_dose |
            |     2 |     ones |     0 |     right |            1 |
            # TODO: Add 1-43198 if/when automated tests are created
            |     2 |     ones | 43199 |     right |        43200 |
            |     2 |     ones | 43200 |     right |        43200 |
            |     3 |     ones |     0 |     right |            1 |
            # TODO: Add 1-28798 if/when automated tests are created
            |     3 |     ones | 28799 |     right |        28800 |
            |     3 |     ones | 28800 |     right |        28800 |
            |     4 |     ones |     0 |     right |            1 |
            # TODO: Add 1-21598 if/when automated tests are created
            |     4 |     ones | 21599 |     right |        21600 |
            |     4 |     ones | 21600 |     right |        21600 |
            |     6 |     ones |     0 |     right |            1 |
            # TODO: Add 1-14398 if/when automated tests are created
            |     6 |     ones | 14399 |     right |        14400 |
            |     6 |     ones | 14400 |     right |        14400 |
            |     8 |     ones |     0 |     right |            1 |
            # TODO: Add 1-10798 if/when automated tests are created
            |     8 |     ones | 10799 |     right |        10800 |
            |     8 |     ones | 10800 |     right |        10800 |
            |    12 |     ones |     0 |     right |            1 |
            # TODO: Add 1-7198 if/when automated tests are created
            |    12 |     ones |  7199 |     right |         7200 |
            |    12 |     ones |  7200 |     right |         7200 |
            |    24 |     ones |     0 |     right |            1 |
            # TODO: Add 1-3598 if/when automated tests are created
            |    24 |     ones |  3599 |     right |         3600 |
            |    24 |     ones |  3600 |     right |         3600 |
            |    48 |     ones |     0 |     right |            1 |
            # TODO: Add 1-1798 if/when automated tests are created
            |    48 |     ones |  1799 |     right |         1800 |
            |    48 |     ones |  1800 |     right |         1800 |
            |    96 |     ones |     0 |     right |            1 |
            # TODO: Add 1-898 if/when automated tests are created
            |    96 |     ones |   899 |     right |          900 |
            |    96 |     ones |   900 |     right |          900 |
            |   192 |     ones |     0 |     right |            1 |
            # TODO: Add 1-498 if/when automated tests are created
            |   192 |     ones |   499 |     right |          500 |
            |   192 |     ones |   500 |     right |          500 |
