//  Created by Andrew Florjancic on 9/18/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef StorageManager_h
#define StorageManager_h

#include <Arduino.h>

// Manages device storage
class StorageManager {
    public:
        // StorageManager constructor that initializes current application settings.
        // If the first byte stored in EEPROM contains a true value then the current settings will be initialized with the factory default settings.
        // Otherwise, the current settings will be initialized with the settings stored on the device.
        StorageManager();

        // Unique identifiers for each pump connected to the Arduino board.
        enum PumpID { pump_1, pump_2, pump_3 };

        // @return The current brightness setting value.
        uint8_t getBrightness();

        // Updates the current brightness setting value and saves to device storage.
        // @param new_value: The new brightness setting value.
        void updateBrightness(uint8_t new_value);

        // @return The current contrast setting value.
        uint8_t getContrast();

        // Updates the current contrast setting value and saves to device storage.
        // @param new_value: The new contrast setting value.
        void updateContrast(uint8_t new_value);

        // Returns the current duty_cycle setting value for the specified pump.
        // @param pump_id: The identifier of the pump.
        // @return The current duty_cycle setting value for the pump associated with the provided PumpID.
        uint8_t getDutyCycle(PumpID pump_id);

        // Updates the current duty_cycle setting value for the specified pump and saves to device storage.
        // @param pump_id: The identifier of the pump.
        // @param new_value: The new duty_cycle setting value.
        void updateDutyCycle(PumpID pump_id, uint8_t new_value);

        // Returns the current dose_frequency setting value for the specified pump.
        // @param pump_id: The identifier of the pump.
        // @return The current dose_frequency setting value for the pump associated with the provided PumpID.
        uint8_t getDoseFrequency(PumpID pump_id);

        // Updates the current dose_frequency setting value for the specified pump and saves to device storage.
        // @param pump_id: The identifier of the pump.
        // @param new_value: The new dose_frequency setting value.
        void updateDoseFrequency(PumpID pump_id, uint8_t new_value);

        // Returns the current dose_duration setting value for the specified pump.
        // @param pump_id: The identifier of the pump.
        // @return The current dose_duration setting value for the pump associated with the provided PumpID.
        unsigned long getDoseDuration(PumpID pump_id);

        // Updates the current dose_duration setting value for the specified pump and saves to device storage.
        // @param pump_id: The identifier of the pump.
        // @param new_value: The new dose_duration setting value.
        void updateDoseDuration(PumpID pump_id, unsigned long new_value);

        // Returns the current dosing_enabled setting value for the specified pump.
        // @param pump_id: The identifier of the pump.
        // @return The current dosing_enabled setting value for the pump associated with the provided PumpID.
        bool getDosingEnabled(PumpID pump_id);

        // Updates the current dosing_enabled setting value for the specified pump and saves to device storage.
        // @param pump_id: The identifier of the pump.
        // @param new_value: The new dosing_enabled setting value.
        void updateDosingEnabled(PumpID pump_id, bool new_value);

        // Resets all PumpSettings setting values for the specified pump to the factory default values.
        // @param pump_id: The identifier of the pump.
        void resetPumpSettings(PumpID pump_id);

        // Resets all settings to the factory default values.
        void factoryReset();
    private:
        // Writes all current settings to device storage.
        void saveSettings();

        // Directory of EEPROM addresses for accessing data saved to the device.
        const struct Directory {
            // EEPROM address used to determine if the storage has been initialized.
            // Locations that have never been written to have the value of 255 so a new board will contain true value.
            const uint8_t use_defaults_address = 0;

            // EEPROM address of the app settings data.
            const uint8_t settings_address = 1;
        } directory;
    
        // Settings used by the application.
        struct AppSettings {
            // Settings used for pump operation.
            struct PumpSettings {
                unsigned long dose_duration; // The number of seconds the pump will stay on for each dose.
                bool dosing_enabled; // True, if the pump should execute its dosing schedule.
                uint8_t dose_frequency; // The number of times the pump will dose in a 24 hour period.
                uint8_t duty_cycle; // The duty cycle the pump should operate at.
            };
            PumpSettings pump1; // Pump settings for pump 1.
            PumpSettings pump2; // Pump settiings for pump 2.
            PumpSettings pump3; // Pump settings for pump 3.
            uint8_t brightness; // Brightness setting percentage value.
            uint8_t contrast; // Contrast setting percentage value.
        };

        // The current settings in use by the application.
        AppSettings current_settings;

        // Default settings for the very first application launch and factory resets.
        const struct Defaults {
            /*
            Default pump settings.

            dose_duration: 10 seconds
            dose_enabled: false
            dose_frequency: 2 times/day
            duty_cycle: 255 
            TODO: update the default duty_cycle to something closer to the calibrated value. It would be better to provide a slightly lower initial
            value as to not potentially overflow the graduated cylinder when performing a calibration.
            */
            const AppSettings::PumpSettings pump_settings = { 10, false, 2, 255 };

            /*
            Default application settings.
            
            pump1: default_pump_settings
            pump2: default_pump_settings
            pump3: default_pump_settings
            brightness: 255 - max brightness
            contrast: 255 - max contrast
            */
            const AppSettings app_settings = { pump_settings, pump_settings, pump_settings, 255, 255 };

        } defaults;

        // Returns the current pump settings for the specified pump.
        // @param pump_id: The identifier of the pump.
        // @return The current pump settings for the pump associated with the provided PumpID.
        StorageManager::AppSettings::PumpSettings &getPumpSettings(StorageManager::PumpID pump_id);
};
#endif
