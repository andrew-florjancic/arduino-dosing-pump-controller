//  Created by Andrew Florjancic on 9/18/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#include <EEPROM.h>
#include "StorageManager.h"

StorageManager::StorageManager() {
    bool use_defaults;
    EEPROM.get(directory.use_defaults_address, use_defaults);
    if(use_defaults) {
        // Initialize current settings with default settings.
        current_settings = defaults.app_settings;
        // Save current settings to EEPROM.
        EEPROM.put(directory.settings_address, current_settings);
        // Update use defaults value to false so that the next time the device is powered on we use the stored settings.
        EEPROM.put(directory.use_defaults_address, false);
    } else {
        EEPROM.get(directory.settings_address, current_settings);
    }
}

void StorageManager::saveSettings() {
    EEPROM.put(directory.settings_address, current_settings);
}

void StorageManager::resetPumpSettings(PumpID pump_id) {
    getPumpSettings(pump_id) = defaults.pump_settings;
    saveSettings();
}

void StorageManager::factoryReset() {
    EEPROM.put(directory.use_defaults_address, true);
    // TODO: Restart the device. The board has a physical reset pin but there should also be a way to do this from software.
}

StorageManager::AppSettings::PumpSettings &StorageManager::getPumpSettings(PumpID pump_id) {
    switch(pump_id) {
        case pump_1: return current_settings.pump1;
        case pump_2: return current_settings.pump2;
        case pump_3: return current_settings.pump3;
    }
}

uint8_t StorageManager::getBrightness() {
    return current_settings.brightness;
}

void StorageManager::updateBrightness(uint8_t new_value) {
    current_settings.brightness = new_value;
    saveSettings();
}

uint8_t StorageManager::getContrast() {
    return current_settings.contrast;
}

void StorageManager::updateContrast(uint8_t new_value) {
    current_settings.contrast = new_value;
    saveSettings();
}

uint8_t StorageManager::getDutyCycle(PumpID pump_id) {
    return getPumpSettings(pump_id).duty_cycle;
}

void StorageManager::updateDutyCycle(PumpID pump_id, uint8_t new_value) {
    getPumpSettings(pump_id).duty_cycle = new_value;
    saveSettings();
}

uint8_t StorageManager::getDoseFrequency(PumpID pump_id) {
    return getPumpSettings(pump_id).dose_frequency;
}

void StorageManager::updateDoseFrequency(PumpID pump_id, uint8_t new_value) {
    getPumpSettings(pump_id).dose_frequency = new_value;
    saveSettings();
}

unsigned long StorageManager::getDoseDuration(PumpID pump_id) {
   return getPumpSettings(pump_id).dose_duration;
}

void StorageManager::updateDoseDuration(PumpID pump_id, unsigned long new_value) {
    getPumpSettings(pump_id).dose_duration = new_value;
    saveSettings();
}

bool StorageManager::getDosingEnabled(PumpID pump_id) {
    return getPumpSettings(pump_id).dosing_enabled;
}

void StorageManager::updateDosingEnabled(PumpID pump_id, bool new_value) {
    getPumpSettings(pump_id).dosing_enabled = new_value;
    saveSettings();
}
