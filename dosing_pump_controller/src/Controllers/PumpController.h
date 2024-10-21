//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#ifndef PumpController_h
#define PumpController_h

#include <Arduino.h>
#include <Motor.h>
#include "../Managers/StorageManager.h"

// Controls pump operation and communicates with the StorageManager to update to pump settings.
class PumpController {
    public:
        // Identification value of the pump being controller.
        StorageManager::PumpID pump_id;

        // Number of milliseconds in 24 hours.
        const unsigned long day_length = 86400000;

        /* Constructor creates a PumpController.
        * @param pump_id: The identifier of the pump that will be controlled.
        * @param storage_manager: The StorageManager used to update pump settings.
        * @param motor: The motor connected to the pump head that will be controlled.*/
        PumpController(StorageManager::PumpID pump_id, StorageManager& storage_manager, Motor& motor);

        // Sets the controller's calibration completion function.
        // @param calibration_completion: A callback function to be executed when calibration has finished.
        void setup(void (*calibration_completion)());

        // Checks the pump status and turns the pump on or off if the right conditions are met.
        // This should called in the Arduino's `loop()` function in the main sketch.
        // @param current_time: The current time in milliseconds.
        void pollPumpStatus(unsigned long current_time);

        // Starts the dosing schedule. Note: First dose will be skipped.
        void startDosing(unsigned long current_time);

        // Stops the dosing schedule and turns the pump off.
        void stopDosing();

        // Turns the pump on.
        void activate();

        // Turns the pump off.
        void deactivate();

        // Turns the pump on until the calibration period is over.
        // @param current_time: The current time, in milliseconds, used to determine when the calibration should stop.
        void calibrate(unsigned long current_time);

        // Resets the pump settings to factory default values.
        void resetPumpSettings();

        // @return The current duty cycle setting for the pump.
        uint8_t getDutyCycle();

        // @return The length of time, in seconds, the pump will be on for each dose.
        unsigned long getDoseDuration();

        // @return The number of doses per day that have been scheduled.
        uint8_t getDoseFrequency();

        // @return True, if the pump should dose its current dosing schedule, otherwise false.
        bool getDosingEnabled();

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
        // @return The length of time in seconds between each scheduled dose.
        unsigned long getIntervalDuration();

        // True, if the pump should be turned off and returnedd to manual mode. Only an ISR should modify this boolean to avoid race conditions.
        // `pollPumpStatus()` will check this boolean and reset.
        bool needs_deactivation = false;

        // True if the pump is waiting for the correct time to turn the pump on for a dose. False if the pump is waiting to turn off after the dose has completed.
        bool needs_dose = false;
        enum PumpMode { manual, calibrating, dosing }; // Possible states the pump can be in.
        PumpMode pump_mode = manual; // The current state of the pump.
        uint8_t duty_cycle; // The current duty_cycle pump setting value, the PWM duty cycle the pump will operate at.
        uint8_t dose_frequency; // The current dose_frequency pump setting value, number of times per day the dose should be delivered.
        unsigned long dose_duration; // The current dose_duration pump setting value, how long each dose will last in milliseconds.
        unsigned long interval_duration; // The length of time in seconds between each scheduled dose.
        unsigned long previous_dose_start_time; // The time, in milliseconds, when the previous dose started.
        const unsigned long calibration_duration = 100000; // The length of time, in milliseconds, pump calibration will last. 100 seconds at 1 mL/s.
        unsigned long calibration_start_time = 0; // The time when calibration started.
        void (*calibration_completion)(); // A callback function to be executed when calibration has finished.
        bool dosing_enabled; // True if the pump should be dosing during its set dosing schedule.
        StorageManager& storage_manager; // The StorageManager used to update settings.
        Motor& motor; // The Motor being controlled.
};
#endif
