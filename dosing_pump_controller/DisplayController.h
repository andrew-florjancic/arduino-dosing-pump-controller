//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef DisplayController_h
#define DisplayController_h

#include <DoublyLinkedList.h>
#include <Display.h>
#include "StorageManager.h"

// Controls the LCD Display and handles updates to brightness and contrast settings.
class DisplayController {
    private:
        const StorageManager& storage_manager; // The StorageManager used to update display settings.
        const DoublyLinkedList<uint8_t> brightness_menu; // Brightness percentages to select from.
        const DoublyLinkedList<uint8_t> contrast_menu; // Contrast percentages to select from.
        Display display; // The Display object

        // Sets the LCD brightness to the current brightness percentage.
        void setLCDBrightness();

        // Sets the LCD contrast to the current contrast percentage.
        void setLCDContrast();
    public:
        // Constructor created a DisplayController.
        // @param display: The Display that will be controlled.
        // @param storage_manager: The StorageManager used to update display settings.
        DisplayController(Display& display, StorageManager& storage_manager);
        
        // Sets up the LCD and sets the brightness and contrast percentages.
        void setup();
        
        // Moves the current item in the brightness menu to the next item and updates the LCD brightness with the current value.
        void increaseBrightness();

        // Moves the current item in the brightness menu to the previous item and updates the LCD brightness with the current value.
        void decreaseBrightness();

        // Saves the current brightness percentage to EEPROM.
        void saveBrightness();

        // @return The current brightness percentage value.
        uint8_t currentBrightness();

        // Moves the current item in the contrast menu to the next item and updates the LCD contrast with the current value.
        void increaseContrast();

        // Moves the current item in the contrast menu to the previous item and updates the LCD contrast with the current value.
        void decreaseContrast();

        // Saves the current contrast percentage value to EEPROM.
        void saveContrast();

        // @return The current contrast percentage value.
        uint8_t currentContrast();
};
#endif
