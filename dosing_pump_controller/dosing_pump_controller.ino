//  Created by Andrew Florjancic on 9/17/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved

#include <Arduino.h>
#include <Display.h>
#include <MenuItem.h>
#include <Menu.h>
#include <Motor.h>
#include <RotaryEncoder.h>
#include "src/Managers/StorageManager.h"
#include "src/Controllers/PumpController.h"
#include "src/Controllers/DisplayController.h"
#include "src/MenuItems/StartDosingMenuItem.h"
#include "src/MenuItems/ReturnMenuItem.h"
#include "src/MenuItems/BrightnessMenuItem.h"
#include "src/MenuItems/ContrastMenuItem.h"
#include "src/MenuItems/SetDoseMenuItem.h"
#include "src/MenuItems/EnablePumpMenuItem.h"
#include "src/MenuItems/PrimePumpMenuItem.h"
#include "src/MenuItems/CalibratePumpMenuItem.h"
#include "src/MenuItems/ResetPumpSettingsMenuItem.h"
#include "src/MenuItems/ComingSoonMenuItem.h"

// A model of the Arduino Nano Every board being used for the dosing pump controller.
struct Board {
  // Pin numbers with a description of their useage.
  const struct Pins {
    uint8_t d13 = 13,  // Pin #1: D13 - unused 
                       // Pin #2: +3V - unused
                       // Pin #3: AREF - unused
            d14 = 14,  // Pin #4: D14 - Connected to LCD pin#6 EN
            d15 = 15,  // Pin #5: D15 - Connected to LCD pin#11 D4
            d16 = 16,  // Pin #6: D16 - Connected to LCD pin#12 D5
            d17 = 17,  // Pin #7: D17 - Connected to LCD pin#13 D6
            d18 = 18,  // Pin #8: D18 - Connected to LCD pin#14 D7
            d19 = 19,  // Pin #9: D19 - Connected to Rotary Encoder ENC_B
            d20 = 20,  // Pin #10: D20 - Connected to Rotary Encoder ENC_A
            d21 = 21,  // Pin #11: D21 - Connected to Rotary Encoder switch
                       // Pin #12: +5V - Connected to positive rail
                       // Pin #13: Reset - unused
                       // Pin #14: GND - Connected to negative rail
                       // Pin #15: VIN - Connected to power supply positive wire
                       // Pin #16: TX - unused
                       // Pin #17: RX - unused
                       // Pin #18: Reset - unused
                       // Pin #19: GND - unused
            d2 = 2,    // Pin #20: D2 - unused
            d3 = 3,    // Pin #21: D3 PWM  - Connected to LCD pin#15 to control brightness
            d4 = 4,    // Pin #22: D4 - unused
            d5 = 5,    // Pin #23: D5 PWM - Connected to LCD pin#3 to control contrast
            d6 = 6,    // Pin #24: D6 PWM - Connected to Motor1 IN2
            d7 = 7,    // Pin #25: D7 - unused
            d8 = 8,    // Pin #26: D8 - unused
            d9 = 9,    // Pin #27: D9 PWM - Connected to Motor2 IN2
            d10 = 10,  // Pin #28: D10 PWM - Connected to Motor3 IN2
            d11 = 11,  // Pin #29: D11 - unused
            d12 = 12;  // Pin #30: D12 - Connected to LCD pin#4
  } pins;

  StorageManager storage_manager = StorageManager();
  RotaryEncoder rotary_encoder = RotaryEncoder(pins.d19, pins.d20, pins.d21, 150);
  Display display = Display(LiquidCrystal(pins.d12, pins.d14, pins.d15, pins.d16, pins.d17, pins.d18), 2, 16, &pins.d3, &pins.d5);
  DisplayController display_controller = DisplayController(display, storage_manager);
  Menu main_menu = Menu("Main Menu");
  Menu settings_menu = Menu("Settings");
  
  Motor motor1 = Motor(nullptr, &pins.d6),
        motor2 = Motor(nullptr, &pins.d9),
        motor3 = Motor(nullptr, &pins.d10);
  // A PumpController and a Menu.
  struct DosingPump {
    PumpController controller;
    Menu menu;
  } pump1 = {PumpController(StorageManager::PumpID::pump_1, storage_manager, motor1), Menu("Pump 1")},
    pump2 = {PumpController(StorageManager::PumpID::pump_2, storage_manager, motor2), Menu("Pump 2")},
    pump3 = {PumpController(StorageManager::PumpID::pump_3, storage_manager, motor3), Menu("Pump 3")};
} board;

// Create calibrate pump menu items. These need to be created now so they can be called by the return control functions.
CalibratePumpMenuItem calibrate_pump1(board.pump1.controller), calibrate_pump2(board.pump2.controller), calibrate_pump3(board.pump3.controller);

// Returns control to the main_menu, to be used as the completion for menu items added to the main_menu.
void mainMenuReturnControl() { board.main_menu.present(); }

// Returns control to the pump1_menu, to be used as the completion for menu items added to the pump1_menu.
void pump1MenuReturnControl() { board.pump1.menu.present(); }

// Returns control to the pump2_menu, to be used as the completion for menu items added to the pump2_menu.
void pump2MenuReturnControl() { board.pump2.menu.present(); }

// Returns control to the pump3_menu, to be used as the completion for menu items added to the pump3_menu.
void pump3MenuReturnControl() { board.pump3.menu.present(); }

// Returns control to the settings_menu, to be used as the completion for menu items added to the settings_menu.
void settingsMenuReturnControl() { board.settings_menu.present(); }

// Returns control the the CalibratePumpMenuItem for pump 1 after calibration has ended.
void pump1CalibrationCompletion() { calibrate_pump1.calibrationComplete(); }

// Returns control the the CalibratePumpMenuItem for pump 2 after calibration has ended.
void pump2CalibrationCompletion() { calibrate_pump2.calibrationComplete(); }

// Returns control the the CalibratePumpMenuItem for pump 3 after calibration has ended.
void pump3CalibrationCompletion() { calibrate_pump3.calibrationComplete(); }

// Triggered by the ISR for the Rotary Encoder push button.
// Sends an input to the rotary encoder to handle debounce.
void buttonInput() { board.rotary_encoder.buttonInput(millis()); }

// Triggered by the ISR for the rotary encoder A pin value changes.
void encoderAInput() { board.rotary_encoder.encodeA(); }

// Triggered by the ISR for the rotary encoder B pin value changes.
void encoderBInput() { board.rotary_encoder.encodeB(); }

// A callback function the RotaryEncoder will call every time a RotaryEncoder Action is detected.
void actionDetected(RotaryEncoder::Actions action) { board.main_menu.sendAction(action); }

void addPumpMenuItems(PumpController& pump_controller, Menu& menu, CalibratePumpMenuItem& calibrate_pump, void (*return_control)()) {
  menu.addMenuItem(new ReturnMenuItem(), return_control);
  menu.addMenuItem(new ComingSoonMenuItem("Info"), return_control);
  menu.addMenuItem(new SetDoseMenuItem(pump_controller), return_control);
  menu.addMenuItem(new EnablePumpMenuItem(pump_controller), return_control);
  menu.addMenuItem(new PrimePumpMenuItem(pump_controller), return_control);
  menu.addMenuItem(&calibrate_pump, return_control);
  menu.addMenuItem(new ResetPumpSettingsMenuItem(pump_controller), return_control);
}

void setup() {
  // Setup display and controllers.
  board.display.setup();
  board.display_controller.setup();
  board.rotary_encoder.setup(&encoderAInput, &encoderBInput, &buttonInput, &actionDetected);
  board.pump1.controller.setup(&pump1CalibrationCompletion);
  board.pump2.controller.setup(&pump2CalibrationCompletion);
  board.pump3.controller.setup(&pump3CalibrationCompletion);

  // Configure the main menu and add menu items.
  board.main_menu.configurePresentable(&board.display, nullptr);
  board.main_menu.addMenuItem(new StartDosingMenuItem(board.pump1.controller, board.pump2.controller, board.pump3.controller), &mainMenuReturnControl);
  board.main_menu.addMenuItem(&board.pump1.menu, &mainMenuReturnControl);
  board.main_menu.addMenuItem(&board.pump2.menu, &mainMenuReturnControl);
  board.main_menu.addMenuItem(&board.pump3.menu, &mainMenuReturnControl);
  board.main_menu.addMenuItem(&board.settings_menu, &mainMenuReturnControl);

  // Add items to the pump menus.
  addPumpMenuItems(board.pump1.controller, board.pump1.menu, calibrate_pump1, &pump1MenuReturnControl);
  addPumpMenuItems(board.pump2.controller, board.pump2.menu, calibrate_pump2, &pump2MenuReturnControl);
  addPumpMenuItems(board.pump3.controller, board.pump3.menu, calibrate_pump3, &pump3MenuReturnControl);

  //Add items to the settings_menu
  board.settings_menu.addMenuItem(new ReturnMenuItem(), &settingsMenuReturnControl);
  board.settings_menu.addMenuItem(new BrightnessMenuItem(board.display_controller), &settingsMenuReturnControl);
  board.settings_menu.addMenuItem(new ContrastMenuItem(board.display_controller), &settingsMenuReturnControl);
  board.settings_menu.addMenuItem(new ComingSoonMenuItem("Set Time"), &settingsMenuReturnControl);
  board.settings_menu.addMenuItem(new ComingSoonMenuItem("Reset All"), &settingsMenuReturnControl);

  // Present the main menu and start dosing.
  board.main_menu.present();
  board.main_menu.sendAction(RotaryEncoder::Actions::select);
}

void loop() {
  unsigned long current_time = millis();
  board.pump1.controller.pollPumpStatus(current_time);
  board.pump2.controller.pollPumpStatus(current_time);
  board.pump3.controller.pollPumpStatus(current_time);
}
