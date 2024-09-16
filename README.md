# arduino-dosing-pump-controller
An Arduino based peristaltic pump controller for dosing specified quantities of liquid at scheduled intervals.

## Overview
I currently need to dose calcium hydroxide, ammonium bicarbonate, and trisodium phosphate solutions to my saltwater aquarium daily to replace alkalinity, calcium, nitrogen, and phosphate that are consumed and by the corals and other organisms. There are plenty of dosing pumps on the market that I could purchase to automate this dosing process, but that's no fun so I'm going to build my own. Even though I'm building this dosing pump controller for a specific use case, it can be used for other applications that require dosing specific quantites of liquid at scheduled intervals throughout the day.

## Feature Overview
### Main Menu Feature
A menu that allows a user to navigate and select the following menu options:
* Start Dosing: Start dosing each pump according to their set dosing schedule.
* Pump 1 Menu - A menu with settings options for pump 1. See Pump Menu Feature below for details on Features included
* Pump 2 Menu - A menu with settings options for pump 2. See Pump Menu Feature below for details on Features included
* Pump 3 Menu - A menu with settings options for pump 3. See Pump Menu Feature below for details on Features included
* Settings Menu - A menu with settings options for the entire application. See Settings Menu Feature below for features included in the Settings Menu.  

### Pump Menu Feature
A menu that allows a user to navigate and select from the following menu options:
* Display Pump Information - Displays all of the current pump settings and information about the pump.
* Set Dose Frequency - Ability for the user to set the number of times per day the pump will deliver a dose. This setting should be stored in non-volitile memory that will persist between power cycles.
* Set Dose - Ability for the user to set the amount of liquid deliverd in each dose. This setting should be stored in non-volitile memory that will persist between power cycles.
* Enable/Disable Pump - Ability for the user to enable or disable a pump so that it can be turned off if not currently in use. This setting should be stored in non-volitile memory that will persist between power cycles.
* Manual Pump Operation - Ability for the user to manually turn the pump on then off in order to prime the tubing with liquid or flush the tubing with a cleaning solution.
* Calibrate Pump - Ability for the user to specify the speed the pump operates at to calibrate the pump for a more accurate dose. This setting should be stored in non-volitile memory that will persist between power cycles. 
* Factory Reset - Ability for the user to reset the pump to its factory default settings. This setting should be stored in non-volitile memory that will persist between power cycles.

### Settings Menu Feature
A menu that allows a user to navigate and select from the following options:
* LCD Brightness Adjustment - Ability for the user to set the brightness level of the LCD. This setting should be stored in non-volitile memory that will persist between power cycles.
* LCD Contrast Adjustment - Ability for the user to set the contrast level of the LCD. This setting should be stored in non-volitile memory that will persist between power cycles.
* Factory Reset - Ability for the user to perform a factory reset that resets all saved application settings to default settings. This setting should be stored in non-volitile memory that will persist between power cycles.


## Device Specifications
* Microcontroller: Arduino Nano Every
* Dosing Pumps: Three Kamoer NKP peristaltic dosing pumps with 3mm ID x 5mm OD tubing.
* Motor Drivers: Three DRV8871 motor drivers.
* Input: Rotary Encoder with push button.
* Display: 16x2 LCD with LED backlight.
* Power supply: 12V DC 1.0A.

## Required Arduino Libraries
* Arduino
* EEPROM
* LiquidCrystal

## Controller Demo
TODO
