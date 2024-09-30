//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#include "DisplayController.h"

DisplayController::DisplayController(const Display& display, const StorageManager& storage_manager)
: display(display), storage_manager(storage_manager) { 
    brightness_menu = DoublyLinkedList<uint8_t>();
    contrast_menu = DoublyLinkedList<uint8_t>();
    // Append percentages 0-100 in increments of 5
    for(uint8_t i = 0; i <= 20; i++) {
        brightness_menu.append(i*5);
        contrast_menu.append(i*5);
    }
    // Set the current brightness and contrast menu items to the values from device storage
    brightness_menu.setCurrentItem(storage_manager.getBrightness());
    contrast_menu.setCurrentItem(storage_manager.getContrast());
}

void DisplayController::setLCDBrightness() {
    // Convert percentage value to uint8_t value
    uint8_t brightness = ((double)brightness_menu.getCurrentItem()->data / 100.00) * 255.00; 
    display.setBrightness(brightness);
}

void DisplayController::setLCDContrast() {
    // Convert percentage value to uint8_t value
    uint8_t contrast = ((double)contrast_menu.getCurrentItem()->data / 100.00) * 255.00;
    display.setContrast(contrast);
}

void DisplayController::saveContrast() {
    storage_manager.updateContrast(contrast_menu.getCurrentItem()->data);
}

void DisplayController::saveBrightness() {
    storage_manager.updateBrightness(brightness_menu.getCurrentItem()->data);
}

void DisplayController::setup() {
    setLCDBrightness();
    setLCDContrast();
}

void DisplayController::increaseBrightness() {
    brightness_menu.nextItem();
    setLCDBrightness();
}

void DisplayController::decreaseBrightness() {
    brightness_menu.previousItem();
    setLCDBrightness();
}

uint8_t DisplayController::currentBrightness() {
    return brightness_menu.getCurrentItem()->data;
}

void DisplayController::increaseContrast() {
    contrast_menu.nextItem();
    setLCDContrast();
}

void DisplayController::decreaseContrast() {
    contrast_menu.previousItem();
    setLCDContrast();
}

uint8_t DisplayController::currentContrast() {
    return contrast_menu.getCurrentItem()->data;
}
