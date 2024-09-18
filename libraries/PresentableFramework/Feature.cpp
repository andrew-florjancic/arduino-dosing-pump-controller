//  Created by Andrew Florjancic on 9/17/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#include "Feature.h"

Feature::Feature() { }

void Feature::showError(uint8_t code) {
    display.lcd.clear();
    display.lcd.print(error_message);
    display.lcd.setCursor(0,1);
    display.lcd.print(error_code_message + String(code));
}