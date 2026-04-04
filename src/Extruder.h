#ifndef EXTRUDER_H
#define EXTRUDER_H

#include <Arduino.h>
#include "../lib/Motor/Motor.h"
#include "../lib/Thermistor/Thermistor.h"
#include "../lib/PIDController/PIDController.h"
#include "../include/PinConfig.h"

class Extruder
{
private:
    Motor _motor;
    Thermistor _thermistor;
    PIDController _pidController;
    
    uint8_t _targetTemperature;
    uint8_t _targetSpeed;
    float _currentTemperature;
    unsigned long _lastPIDTime;
    bool _heaterEnabled;

public:
    Extruder();

    void begin();
    void update();

    void setTargetTemperature(uint8_t temp);
    void setTargetSpeed(uint8_t speed);
    uint8_t getTargetTemperature() const;
    uint8_t getTargetSpeed() const;
    float getCurrentTemperature() const;
    bool isHeaterEnabled() const;
    void setHeaterEnabled(bool enabled);
};

#endif
