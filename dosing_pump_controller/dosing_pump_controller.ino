//  Created by Andrew Florjancic on 9/17/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved

#include <Arduino.h>
#include <Display.h>
#include <MenuItem.h>
#include <Menu.h>
#include <Motor.h>
#include <RotaryEncoder.h>
#include "StorageManager.h"
#include "PumpController.h"
#include "DisplayController.h"

StorageManager storage_manager;

// TODO: Throw all these pins in a struct or something that can represent the Nano Every board that is being used.
const uint8_t rs = 12, en = 14, d4 = 15, d5 = 16, d6 = 17, d7 = 18;
const uint8_t lcd_rows = 2, lcd_columns = 16, lcd_backlight = 3; 

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// TODO: Connect contrast pin to one of the Arduino PWM pins - currently controlling LCD contrast with a potentiometer.
Display display(lcd, lcd_rows, lcd_columns, &lcd_backlight, nullptr);
DisplayController display_controller(display, storage_manager);

// TODO: Update this with the actual pins connected to the motors
Motor motor1(nullptr, nullptr);
Motor motor2(nullptr, nullptr);
Motor motor3(nullptr, nullptr);

PumpController pump1_controller(StorageManager::PumpID::pump_1, storage_manager, motor1);
PumpController pump2_controller(StorageManager::PumpID::pump_2, storage_manager, motor2);
PumpController pump3_controller(StorageManager::PumpID::pump_3, storage_manager, motor3);

// Create menus now so that the completion methods can call the menu's present() method
Menu main_menu("Main Menu");
Menu pump1_menu("Pump 1");
Menu pump2_menu("Pump 2");
Menu pump3_menu("Pump 3");
Menu settings_menu("Settings");

// Returns control to the main_menu, to be used as the completion for menu items added to the main_menu.
void mainMenuReturnControl() {
  main_menu.present();
}

// Returns control to the pump1_menu, to be used as the completion for menu items added to the pump1_menu.
void pump1ReturnControl() {
  pump1_menu.present();
}

// Returns control to the pump2_menu, to be used as the completion for menu items added to the pump2_menu.
void pump2ReturnControl() {
  pump2_menu.present();
}

// Returns control to the pump3_menu, to be used as the completion for menu items added to the pump3_menu.
void pump3ReturnControl() {
  pump3_menu.present();
}

// Returns control to the settings_menu, to be used as the completion for menu items added to the settings_menu.
void settingsMenuReturnControl() {
  settings_menu.present();
}

RotaryEncoder rotary_encoder(1, 2, 21, 150); // TODO add actual pin values. Also 150 milliseconds sounds high for the debounce duration.

// Triggered by the ISR for the Rotary Encoder push button.
// Sends an input to the rotary encoder to handle debounce
void buttonInput() {
  rotary_encoder.buttonInput(millis());
}

// A callback function the RotaryEncoder will call every time a true button press is detected.
void buttonPressed() {
  // TODO: send an input command to the main menu
}


void setup() {
  display.setup();
  rotary_encoder.setup(&buttonInput, &buttonPressed);

  // Configure the main_menu then add items.
  // I don't think I'll ever dismiss the main_menu so this completion can probably be a nullptr.
  // And just as I'm writing this I find myself wanting to be able to dismiss the main menu then turn the LCD brightness to 0 after some period of inactivity.
  // Let's address this concern later.
  main_menu.configurePresentable(&display, nullptr);
  // TODO: Add items to the main menu

  // TODO: Add items to the pump1_menu

  // TODO: Add items to the pump2_menu

  // TODO: Add items to the pump3_menu

  // TODO: Add items to the settings_menu

  main_menu.present();
}

void loop() {
  unsigned long current_time = millis();
  pump1_controller.pollPumpStatus(current_time);
  pump2_controller.pollPumpStatus(current_time); 
  pump3_controller.pollPumpStatus(current_time); 
}
