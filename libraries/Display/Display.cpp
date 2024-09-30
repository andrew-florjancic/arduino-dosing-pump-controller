//  Created by Andrew Florjancic on 9/17/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#include "Display.h"

Display::Display(const LiquidCrystal lcd, uint8_t rows, uint8_t columns, uint8_t* backlight_pin, uint8_t* contrast_pin) 
: lcd(lcd), rows(rows), columns(columns), backlight_pin(backlight_pin), contrast_pin(contrast_pin) { }

void Display::setup() {
    if(backlight_pin != nullptr) { pinMode(*backlight_pin, OUTPUT); } 
    if(contrast_pin != nullptr) { pinMode(*contrast_pin, OUTPUT); }
    lcd.begin(rows, columns);
}

void Display::setBrightness(uint8_t duty_cycle) {
    if(backlight_pin == nullptr) { return; }
    analogWrite(*backlight_pin, duty_cycle);
}

void Display::setContrast(uint8_t duty_cycle) {
    if(contrast_pin == nullptr) { return; }
    analogWrite(*contrast_pin, duty_cycle);
}