# arduino-dosing-pump-controller
An Arduino based peristaltic pump controller for dosing specified quantities of liquid at scheduled intervals.

## Overview
I currently need to dose calcium hydroxide, ammonium bicarbonate, and trisodium phosphate solutions to my saltwater aquarium daily to replace alkalinity, calcium, nitrogen, and phosphate that are consumed and by the corals and other organisms. There are plenty of dosing pumps on the market that I could purchase to automate this dosing process, but that's no fun so I'm going to build my own. Even though I'm building this dosing pump controller for a specific use case, it can be used for other applications that require dosing specific quantites of liquid at scheduled intervals throughout the day.

## Application Structure
Main Menu
* Start Dosing - Starts dosing on each pumps set schedule if the pump is enabled.
* Pump 1 Menu
  * Return - Returns the user to the Main Menu.
  * Info - Coming Soon: Will display current pump settings.
  * Set Dose - Allows the user to set the number of doses per day and the dose quantity.
  * Enable Pump - On, if the pump should dose during its set schedule.
  * Prime - Allows the user to manually operate the pump to prime the pump and tubing before calibration or dosing.
  * Calibrate - Set the PWM of the pump motor then operates the pump for 100 seconds.
  * Reset - Resets all pump settings to the factory default settings.
* Pump 2 Menu ...
* Pump 3 Menu ...
* Settings Menu
  * Brightness - Allows the user to adjust the LCD brightness.
  * Contrast - Allows the user to adjust the LCD contrast.
  * Set Time - Coming soon: Will allow the user to set the current time once a RTC is added.
  * Reset All - Resets all settings to the factory default settings

## Demo
<div display="flex">
  <img src="https://github.com/user-attachments/assets/11d0ed5f-e7fe-4f8d-bbd2-d34bb39f2cd4" width="32%" />
  <img src="https://github.com/user-attachments/assets/a9d99f40-7e0d-4f75-ae96-e28a88abcda7" width="32%" />
  <video src="https://github.com/user-attachments/assets/0925db20-e07c-456d-a0bf-7b672bf88164" width="32%" />
</div> 

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

## Usage
This is not intended to be used by anyone but me, if you are reading this you are not authorized to use it. You can look at the code if want.

## TODO
There are a few features I want to add and some modifications I would like to make in the future.
1. Add a Real Time Clock to the circuit - Currently this project is just using Arduino millis() which will start to overflow the unsigned long after about 50 days which is most certianly going to cause some issues. In the meantime it's not a huge hassle to just periodically restart the device.
2. Pump Info Feature: Display all current pump settings, this isn't super important to me but would be a nice to have.
3. Reset All Feature: Needs an update to restart the device automatically, otherwise the user needs to manually restart the device to see the effects.
4. I would like to add additional pumps to the controller but I'm already using all of the Arduino PWM pins, ultimately I'd like to move away from Arduino all together and design a custom PCB so we can also explore some kind of modular pump circuit. Also need to take into consideration power supply limit if all pumps are operating at the same time.
5. Add automated tests and setup the CICD pipeline to require all tests passign before PRs are merged.
6. Some of these libraries I created for this project should probably be in their own repository but we can tackle that later or never.
7. Empty Dosing Container Alert Feature: It would be nice to know when the dosing container is empty or getting close to being empty and start flashing a LED or something.
