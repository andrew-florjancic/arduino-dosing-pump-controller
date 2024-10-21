//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "PumpController.h"

PumpController::PumpController(StorageManager::PumpID pump_id, StorageManager& storage_manager, Motor& motor)
: pump_id(pump_id), storage_manager(storage_manager), motor(motor) {
    duty_cycle = storage_manager.getDutyCycle(pump_id);
    dose_duration = storage_manager.getDoseDuration(pump_id);
    dose_frequency = storage_manager.getDoseFrequency(pump_id);
    dosing_enabled = storage_manager.getDosingEnabled(pump_id);
    interval_duration = day_length / dose_frequency;
}

void PumpController::setup(void (*calibration_completion)()) {
    this->calibration_completion = calibration_completion;
    motor.setup();
}

void PumpController::pollPumpStatus(unsigned long current_time) {
    if(needs_deactivation) {
        motor.off();
        pump_mode = manual;
        needs_deactivation = false;
    }
    switch(pump_mode) {
        case manual: break;
        case calibrating:
            // Deactivate the pump if the calibration period has ended.
            if((calibration_start_time + calibration_duration) <= current_time) {
                deactivate();
                calibration_completion();
            }
            break;
        case dosing:
            if(!dosing_enabled) { break; }
            if(!needs_dose && ((previous_dose_start_time + dose_duration) <= current_time)) {
                motor.off();
                needs_dose = true;
            }
            // Activate the pump and reset the previous dose time if the interval duration is over.
            if(needs_dose && ((previous_dose_start_time + interval_duration) <= current_time)) {
                previous_dose_start_time = current_time;
                needs_dose = false;
                activate();
            }
            break;
    }
}

void PumpController::startDosing(unsigned long current_time) {
    /* Important!
    * An assumption is being made here that once the device is powered on this method will be automatically called to start the dosing schedule so
    * that in the case of a power failure the dosing schedule can resume once power is returned. Because of this assumption, it is an intentional
    * design decision that the pumps must not immediately administer their first dose when this method is called. If we did not delay the dosing
    * schedule, then in the event where multiple power outages occur frequently there would be the potential to overdose which could be disastrous.
    * We are going to err on the side of caution and avoid overdosing in favor of delaying doses or potentially missing doses due to the lower risk.*/
    previous_dose_start_time = current_time;
    needs_dose = false;
    pump_mode = dosing;
}

void PumpController::stopDosing() {
    needs_deactivation = true;
}

void PumpController::activate() {
    motor.forward(duty_cycle);
}

void PumpController::deactivate() {
    motor.off();
    needs_deactivation = false;
    pump_mode = manual;
}

void PumpController::calibrate(unsigned long current_time) {
    calibration_start_time = current_time;
    activate();
    pump_mode = calibrating;
}

void PumpController::resetPumpSettings() {
    storage_manager.resetPumpSettings(pump_id);
    duty_cycle = storage_manager.getDutyCycle(pump_id);
    dose_duration = storage_manager.getDoseDuration(pump_id);
    dose_frequency = storage_manager.getDoseFrequency(pump_id);
    dosing_enabled = storage_manager.getDosingEnabled(pump_id);
    interval_duration = day_length / (unsigned long)dose_frequency;
}

unsigned long PumpController::getIntervalDuration() {
    return interval_duration;
}

uint8_t PumpController::getDutyCycle() {
    return duty_cycle;
}

unsigned long PumpController::getDoseDuration() {
    return dose_duration;
}

uint8_t PumpController::getDoseFrequency() {
    return dose_frequency;
}

bool PumpController::getDosingEnabled() {
    return dosing_enabled;
}

void PumpController::updateDutyCycle(uint8_t new_value) {
    this->duty_cycle = new_value;
    storage_manager.updateDutyCycle(pump_id, new_value);
}

void PumpController::updateDoseDuration(unsigned long new_value) {
    dose_duration = new_value;
    storage_manager.updateDoseDuration(pump_id, new_value);
}

void PumpController::updateDoseFrequency(uint8_t new_value) {
    dose_frequency = new_value;
    interval_duration = day_length / (unsigned long)dose_frequency;
    storage_manager.updateDoseFrequency(pump_id, new_value);
}

void PumpController::updateDosingEnabled(bool new_value) {
    dosing_enabled = new_value;
    storage_manager.updateDosingEnabled(pump_id, new_value);
}
