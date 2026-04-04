#include "Extruder.h"

#define MAX_SAFE_TEMPERATURE 350
#define MIN_SAFE_TEMPERATURE -10

Extruder::Extruder()
    : _motor(STP_PIN, DIR_PIN, EN_PIN),
      _thermistor(TH0_PIN),
      _pidController(3.0f, 0.5f, 0.05f, 0.0f, 255.0f),
      _targetTemperature(200),
      _targetSpeed(50),
      _currentTemperature(0.0f),
      _lastPIDTime(0),
      _heaterEnabled(false)
{
}

void Extruder::begin()
{
    _motor.begin();
    _thermistor.begin();
    pinMode(H0, OUTPUT);
    analogWrite(H0, 0);
}

void Extruder::update()
{
    _thermistor.readTemperature();
    _currentTemperature = _thermistor.getTemperature();

    if (_currentTemperature > MAX_SAFE_TEMPERATURE || _currentTemperature < MIN_SAFE_TEMPERATURE)
    {
        _heaterEnabled = false;
        analogWrite(H0, 0);
        Serial.println(F("ERROR: Temperature out of safe range!"));
    }

    unsigned long currentMillis = millis();
    if (currentMillis - _lastPIDTime >= 500)
    {
        float dt = (currentMillis - _lastPIDTime) / 1000.0f;
        _lastPIDTime = currentMillis;

        if (_heaterEnabled)
        {
            _pidController.setSetpoint(_targetTemperature);
            float output = _pidController.compute(_currentTemperature, dt);
            analogWrite(H0, (uint8_t)output);
        }
        else
        {
            analogWrite(H0, 0);
        }
    }
}

void Extruder::setTargetTemperature(uint8_t temp)
{
    _targetTemperature = temp;
}

void Extruder::setTargetSpeed(uint8_t speed)
{
    _targetSpeed = speed;
    _motor.updateSpeed(_targetSpeed);
}

uint8_t Extruder::getTargetTemperature() const
{
    return _targetTemperature;
}

uint8_t Extruder::getTargetSpeed() const
{
    return _targetSpeed;
}

float Extruder::getCurrentTemperature() const
{
    return _currentTemperature;
}

bool Extruder::isHeaterEnabled() const
{
    return _heaterEnabled;
}

void Extruder::setHeaterEnabled(bool enabled)
{
    _heaterEnabled = enabled;
    if (!enabled)
    {
        analogWrite(H0, 0);
    }
}
