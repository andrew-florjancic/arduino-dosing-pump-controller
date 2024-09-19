//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#ifndef PumpController_h
#define PumpController_h

#include <Arduino.h>
#include <Motor.h>
#include "StorageManager.h"

// Controls pump operation and communicates with the StorageManager to update to pump settings.
class PumpController {
    public:
        // Identification value of the pump being controller.
        const StorageManager::PumpID pump_id;

        // Number of seconds in 24 hours.
        const unsigned long day_length = 86400; // TODO: does this belong somewhere else? 

        /* Constructor creates a PumpController.
        * @param pump_id: The identifier of the pump that will be controlled.
        * @param storage_manager: A pointer to the storage manager. TODO: should this be a pointer?
        * @param motor: The motor connected to the pump head that will be controlled.*/
        PumpController(StorageManager::PumpID pump_id, StorageManager& storage_manager, Motor motor);

        // Sets the controller's calibration completion function.
        // @param calibration_completion: A callback function to be executed when calibration has finished.
        void setup(void (*calibration_completion)());

        // Turns the pump on. For manual operation only
        void activate();

        // Turns the pump off
        void deactivate();

        // Turns the pump on until the calibration period is over.
        // @param current_time: The current time, in milliseconds, used to determine when the calibration should stop.
        void calibrate(unsigned long current_time);

        // Resets the pump settings to factory default values.
        void resetPumpSettings();

        // @return The length of time in seconds between each scheduled dose.
        unsigned long getIntervalDuration();

        // @return The current duty cycle setting for the pump.
        uint8_t getDutyCycle();

        // @return The length of time, in seconds, the pump will be on for each dose.
        unsigned long getDoseDuration();

        // @return The number of doses per day that have been scheduled.
        uint8_t getDoseFrequency();

        // @return True, if the pump should dose its current dosing schedule, otherwise false.
        bool getDosingEnabled(); // TODO: rename to shouldDoseOnSchedule()?

        // Updates the duty_cycle pump setting with a new value.
        // @param new_value: The new duty_cycle value.
        void updateDutyCycle(uint8_t new_value);

        // Updates the dose_duration pump setting with a new value.
        // @param new_value: The new dose_duration value.
        void updateDoseDuration(unsigned long new_value);

        // Updates the dose_frequency pump setting with a new value.
        // @param new_value: The new dose_frequency value.
        void updateDoseFrequency(uint8_t new_value);

        // Updates the dosing_enabled pump setting with a new value.
        // @param  new_value: The new value of the dosing_enabled pump setting.
        void updateDosingEnabled(bool new_value);
    private:
        enum PumpState { off, manual, calibrating, dosing }; // Possible states the pump can be in.
        PumpState pump_state = off; // The current state of the pump.
        const StorageManager& storage_manager; // The StorageManager used to update settings.
        const Motor motor; // The Motor being controlled.
        uint8_t duty_cycle; // The current duty_cycle pump setting value.
        uint8_t dose_frequency; // The current dose_frequency pump setting value.
        unsigned long dose_duration; // The current dose_duration pump setting value.
        unsigned long previous_dose_start_time; // The time, in milliseconds, when the previous dose started.
        unsigned long calibration_duration = 5000; // The length of time, in milliseconds, pump calibration will last. TODO: update this to the actual calibration duration
        unsigned long calibration_start_time = 0; // The time when calibration started.
        void (*calibration_completion)(); // A callback function to be executed when calibration has finished.
        bool dosing_enabled; // True if the pump should be dosing during its set dosing schedule.
};
#endif
