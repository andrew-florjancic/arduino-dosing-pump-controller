Feature: Set Dose feature

    Scenario Outline: User updates doses per day
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
            # TODO: Add 200-43000 if/when automated tests are created
            |     2 | hundreds | 43100 |      left |        43000 |
            |     3 | hundreds |     0 |      left |            0 |
            |     3 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-28600 if/when automated tests are created
            |     3 | hundreds | 28700 |      left |        28600 |
            |     4 | hundreds |     0 |      left |            0 |
            |     4 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-21400 if/when automated tests are created
            |     4 | hundreds | 21500 |      left |        21400 |
            |     6 | hundreds |     0 |      left |            0 |
            |     6 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-14200 if/when automated tests are created
            |     6 | hundreds | 14300 |      left |        14200 |
            |     8 | hundreds |     0 |      left |            0 |
            |     8 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-10600 if/when automated tests are created
            |     8 | hundreds | 10700 |      left |        10600 |
            |    12 | hundreds |     0 |      left |            0 |
            |    12 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-7000 if/when automated tests are created
            |    12 | hundreds |  7100 |      left |         7000 |
            |    24 | hundreds |     0 |      left |            0 |
            |    24 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-3400 if/when automated tests are created
            |    24 | hundreds |  3500 |      left |         3400 |
            |    48 | hundreds |     0 |      left |            0 |
            |    48 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-1600 if/when automated tests are created
            |    48 | hundreds |  1700 |      left |         1600 |
            |    96 | hundreds |     0 |      left |            0 |
            |    96 | hundreds |   100 |      left |            0 |
            # TODO: Add 200-700 if/when automated tests are created
            |    96 | hundreds |   800 |      left |          700 |
            |   192 | hundreds |     0 |      left |            0 |
            |   192 | hundreds |   100 |      left |            0 |
            |   192 | hundreds |   200 |      left |          100 |
            |   192 | hundreds |   300 |      left |          200 |
            |   192 | hundreds |   400 |      left |          300 |

        Scenarios: User turns the rotary encoder to the left when modifying the tens place
            | doses | position |  dose | direction | updated_dose |
            |     2 |     tens |     0 |      left |            0 |
            |     2 |     tens |    10 |      left |            0 |
            # TODO: Add 20-43180 if/when automated tests are created
            |     2 |     tens | 43190 |      left |        43180 |
            |     3 |     tens |     0 |      left |            0 |
            |     3 |     tens |    10 |      left |            0 |
            # TODO: Add 20-28780 if/when automated tests are created
            |     3 |     tens | 28790 |      left |        28780 |
            |     4 |     tens |     0 |      left |            0 |
            |     4 |     tens |    10 |      left |            0 |
            # TODO: Add 20-21580 if/when automated tests are created
            |     4 |     tens | 21590 |      left |        21580 |
            |     6 |     tens |     0 |      left |            0 |
            |     6 |     tens |    10 |      left |            0 |
            # TODO: Add 20-14380 if/when automated tests are created
            |     6 |     tens | 14390 |      left |        14380 |
            |     8 |     tens |     0 |      left |            0 |
            |     8 |     tens |    10 |      left |            0 |
            # TODO: Add 20-10780 if/when automated tests are created
            |     8 |     tens | 10790 |      left |        10780 |
            |    12 |     tens |     0 |      left |            0 |
            |    12 |     tens |    10 |      left |            0 |
            # TODO: Add 20-7180 if/when automated tests are created
            |    12 |     tens |  7190 |      left |         7180 |
            |    24 |     tens |     0 |      left |            0 |
            |    24 |     tens |    10 |      left |            0 |
            # TODO: Add 20-3580 if/when automated tests are created
            |    24 |     tens |  3590 |      left |         3580 |
            |    48 |     tens |     0 |      left |            0 |
            |    48 |     tens |    10 |      left |            0 |
            # TODO: Add 20-1780 if/when automated tests are created
            |    48 |     tens |  1790 |      left |         1780 |
            |    96 |     tens |     0 |      left |            0 |
            |    96 |     tens |    10 |      left |            0 |
            # TODO: Add 20-880 if/when automated tests are created
            |    96 |     tens |   890 |      left |          880 |
            |   192 |     tens |     0 |      left |            0 |
            |   192 |     tens |    10 |      left |            0 |
            # TODO: Add 20-430 if/when automated tests are created
            |   192 |     tens |   440 |      left |          430 |

        Scenarios: User turns the rotary encoder to the left when modifying the ones place
            | doses | position |  dose | direction | updated_dose |
            |     2 |     ones |     0 |      left |            0 |
            |     2 |     ones |     1 |      left |            0 |
            # TODO: Add 2-43198 if/when automated tests are created
            |     2 |     ones | 43199 |      left |        43198 |
            |     3 |     ones |     0 |      left |            0 |
            |     3 |     ones |     1 |      left |            0 |
            # TODO: Add 2-28798 if/when automated tests are created
            |     3 |     ones | 28799 |      left |        28798 |
            |     4 |     ones |     0 |      left |            0 |
            |     4 |     ones |     1 |      left |            0 |
            # TODO: Add 2-21598 if/when automated tests are created
            |     4 |     ones | 21599 |      left |        21598 |
            |     6 |     ones |     0 |      left |            0 |
            |     6 |     ones |     1 |      left |            0 |
            # TODO: Add 2-14398 if/when automated tests are created
            |     6 |     ones | 14399 |      left |        14398 |
            |     8 |     ones |     0 |      left |            0 |
            |     8 |     ones |     1 |      left |            0 |
            # TODO: Add 2-10798 if/when automated tests are created
            |     8 |     ones | 10799 |      left |        10798 |
            |    12 |     ones |     0 |      left |            0 |
            |    12 |     ones |     1 |      left |            0 |
            # TODO: Add 2-7198 if/when automated tests are created
            |    12 |     ones |  7199 |      left |         7198 |
            |    24 |     ones |     0 |      left |            0 |
            |    24 |     ones |     1 |      left |            0 |
            # TODO: Add 2-3598 if/when automated tests are created
            |    24 |     ones |  3599 |      left |         3598 |
            |    48 |     ones |     0 |      left |            0 |
            |    48 |     ones |     1 |      left |            0 |
            # TODO: Add 2-1798 if/when automated tests are created
            |    48 |     ones |  1799 |      left |         1798 |
            |    96 |     ones |     0 |      left |            0 |
            |    96 |     ones |     1 |      left |            0 |
            # TODO: Add 2-898 if/when automated tests are created
            |    96 |     ones |   899 |      left |          898 |
            |   192 |     ones |     0 |      left |            0 |
            |   192 |     ones |     1 |      left |            0 |
            # TODO: Add 2-448 if/when automated tests are created
            |   192 |     ones |   449 |      left |          448 |

        Scenarios: User turn the rotary encoder to the right when modifying the hundreds place
            | doses | position |  dose | direction | updated_dose |
            |     2 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-42900 if/when automated tests are created
            |     2 | hundreds | 43000 |     right |        43100 |
            |     2 | hundreds | 43100 |     right |        43100 |
            |     3 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-28500 if/when automated tests are created
            |     3 | hundreds | 28600 |     right |        28700 |
            |     3 | hundreds | 28700 |     right |        28700 |
            |     4 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-21300 if/when automated tests are created
            |     4 | hundreds | 21400 |     right |        21500 |
            |     4 | hundreds | 21500 |     right |        21500 |
            |     6 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-14100 if/when automated tests are created
            |     6 | hundreds | 14200 |     right |        14300 |
            |     6 | hundreds | 14300 |     right |        14300 |
            |     8 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-10500 if/when automated tests are created
            |     8 | hundreds | 10600 |     right |        10700 |
            |     8 | hundreds | 10700 |     right |        10700 |
            |    12 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-6900 if/when automated tests are created
            |    12 | hundreds |  7000 |     right |         7100 |
            |    12 | hundreds |  7100 |     right |         7100 |
            |    24 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-3300 if/when automated tests are created
            |    24 | hundreds |  3400 |     right |         3500 |
            |    24 | hundreds |  3500 |     right |         3500 |
            |    48 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-1500 if/when automated tests are created
            |    48 | hundreds |  1600 |     right |         1700 |
            |    48 | hundreds |  1700 |     right |         1700 |
            |    96 | hundreds |     0 |     right |          100 |
            # TODO: Add 100-600 if/when automated tests are created
            |    96 | hundreds |   700 |     right |          800 |
            |    96 | hundreds |   800 |     right |          800 |
            |   192 | hundreds |     0 |     right |          100 |
            |   192 | hundreds |   100 |     right |          200 |
            |   192 | hundreds |   200 |     right |          300 |
            |   192 | hundreds |   300 |     right |          400 |
            |   192 | hundreds |   400 |     right |          400 |

        Scenarios: User turns the rotary encoder to the right when modifying the tens place
            | doses | position |  dose | direction | updated_dose |
            |     2 |     tens |     0 |     right |           10 |
            # TODO: Add 10-43170 if/when automated tests are created
            |     2 |     tens | 43180 |     right |        43190 |
            |     2 |     tens | 43190 |     right |        43190 |
            |     3 |     tens |     0 |     right |           10 |
            # TODO: Add 10-28770 if/when automated tests are created
            |     3 |     tens | 28780 |     right |        28790 |
            |     3 |     tens | 28790 |     right |        28790 |
            |     4 |     tens |     0 |     right |           10 |
            # TODO: Add 10-21570 if/when automated tests are created
            |     4 |     tens | 21580 |     right |        21590 |
            |     4 |     tens | 21590 |     right |        21590 |
            |     6 |     tens |     0 |     right |           10 |
            # TODO: Add 10-14370 if/when automated tests are created
            |     6 |     tens | 14380 |     right |        14390 |
            |     6 |     tens | 14390 |     right |        14390 |
            |     8 |     tens |     0 |     right |           10 |
            # TODO: Add 10-10770 if/when automated tests are created
            |     8 |     tens | 10780 |     right |        10790 |
            |     8 |     tens | 10790 |     right |        10790 |
            |    12 |     tens |     0 |     right |           10 |
            # TODO: Add 10-7170 if/when automated tests are created
            |    12 |     tens |  7180 |     right |         7190 |
            |    12 |     tens |  7190 |     right |         7190 |
            |    24 |     tens |     0 |     right |           10 |
            # TODO: Add 10-3570 if/when automated tests are created
            |    24 |     tens |  3580 |     right |         3590 |
            |    24 |     tens |  3590 |     right |         3590 |
            |    48 |     tens |     0 |     right |           10 |
            # TODO: Add 10-1770 if/when automated tests are created
            |    48 |     tens |  1780 |     right |         1790 |
            |    48 |     tens |  1790 |     right |         1790 |
            |    96 |     tens |     0 |     right |           10 |
            # TODO: Add 10-870 if/when automated tests are created
            |    96 |     tens |   880 |     right |          890 |
            |    96 |     tens |   890 |     right |          890 |
            |   192 |     tens |     0 |     right |           10 |
            # TODO: Add 10-420 if/when automated tests are created
            |   192 |     tens |   430 |     right |          440 |
            |   192 |     tens |   440 |     right |          440 |

        Scenarios: User turns the rotary encoder to the right when modifying the ones place
            | doses | position |  dose | direction | updated_dose |
            |     2 |     ones |     0 |     right |            1 |
            # TODO: Add 1-43197 if/when automated tests are created
            |     2 |     ones | 43198 |     right |        43199 |
            |     2 |     ones | 43199 |     right |        43199 |
            |     3 |     ones |     0 |     right |            1 |
            # TODO: Add 1-28797 if/when automated tests are created
            |     3 |     ones | 28798 |     right |        28799 |
            |     3 |     ones | 28799 |     right |        28799 |
            |     4 |     ones |     0 |     right |            1 |
            # TODO: Add 1-21597 if/when automated tests are created
            |     4 |     ones | 21598 |     right |        21599 |
            |     4 |     ones | 21599 |     right |        21599 |
            |     6 |     ones |     0 |     right |            1 |
            # TODO: Add 1-14397 if/when automated tests are created
            |     6 |     ones | 14398 |     right |        14399 |
            |     6 |     ones | 14399 |     right |        14399 |
            |     8 |     ones |     0 |     right |            1 |
            # TODO: Add 1-10797 if/when automated tests are created
            |     8 |     ones | 10798 |     right |        10799 |
            |     8 |     ones | 10799 |     right |        10799 |
            |    12 |     ones |     0 |     right |            1 |
            # TODO: Add 1-7197 if/when automated tests are created
            |    12 |     ones |  7198 |     right |         7199 |
            |    12 |     ones |  7199 |     right |         7199 |
            |    24 |     ones |     0 |     right |            1 |
            # TODO: Add 1-3597 if/when automated tests are created
            |    24 |     ones |  3598 |     right |         3599 |
            |    24 |     ones |  3599 |     right |         3599 |
            |    48 |     ones |     0 |     right |            1 |
            # TODO: Add 1-1797 if/when automated tests are created
            |    48 |     ones |  1798 |     right |         1799 |
            |    48 |     ones |  1799 |     right |         1799 |
            |    96 |     ones |     0 |     right |            1 |
            # TODO: Add 1-897 if/when automated tests are created
            |    96 |     ones |   898 |     right |          899 |
            |    96 |     ones |   899 |     right |          899 |
            |   192 |     ones |     0 |     right |            1 |
            # TODO: Add 1-447 if/when automated tests are created
            |   192 |     ones |   448 |     right |          449 |
            |   192 |     ones |   449 |     right |          449 |
