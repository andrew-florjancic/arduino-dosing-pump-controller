//  Created by Andrew Florjancic on 9/19/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "PumpController.h"

PumpController::PumpController(StorageManager::PumpID pump_id, StorageManager& storage_manager, Motor motor)
: pump_id(pump_id), storage_manager(storage_manager), motor(motor) {
    duty_cycle = storage_manager.getDutyCycle(pump_id);
    dose_duration = storage_manager.getDoseDuration(pump_id);
    dose_frequency = storage_manager.getDoseFrequency(pump_id);
    dosing_enabled = storage_manager.getDosingEnabled(pump_id);
}

void PumpController::setup(void (*calibration_completion)()) {
    this->calibration_completion = calibration_completion;
    motor.setup();
}

void PumpController::pollPumpStatus(unsigned long current_time) {
    switch(pump_state) {
        case off: break;
        case calibrating:
            // Deactivate the pump if the calibration period has ended.
            if(current_time - calibration_start_time >= calibration_duration) {
                deactivate();
                calibration_completion();
            }
            break;
        case dosing:
        // TODO add dosing
        break;
    }
}

void PumpController::activate() {
    pump_state = manual;
    motor.forward(duty_cycle);
}

void PumpController::deactivate() {
    motor.off();
    pump_state = off;
}

void PumpController::calibrate(unsigned long current_time) {
    pump_state = calibrating;
    calibration_start_time = current_time;
    motor.forward(duty_cycle);
}

void PumpController::resetPumpSettings() {
    storage_manager.resetPumpSettings(pump_id);
    duty_cycle = storage_manager.getDutyCycle(pump_id);
    dose_duration = storage_manager.getDoseDuration(pump_id);
    dose_frequency = storage_manager.getDoseFrequency(pump_id);
    dosing_enabled = storage_manager.getDosingEnabled(pump_id);
}

unsigned long PumpController::getIntervalDuration() {
    return dose_frequency / day_length;
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
    storage_manager.updateDoseFrequency(pump_id, new_value);
}

void PumpController::updateDosingEnabled(bool new_value) {
    dosing_enabled = new_value;
    storage_manager.updateDosingEnabled(pump_id, new_value);
}
