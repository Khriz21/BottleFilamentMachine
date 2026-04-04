#include <Arduino.h>

#ifndef THERMISTOR_H
#define THERMISTOR_H

class Thermistor
{
private:
    uint8_t _pinThermistor;

    const unsigned long _interval; // Interval for reading temperature in milliseconds
    unsigned long _lastReadTime; // Timestamp of the last temperature reading

    float _temperature; // Current temperature reading
    unsigned long _currentTime; // Current timestamp for timing control
    float _voltage; // Voltage across the thermistor
    float _ntcResistance; // Resistance of the thermistor
    float _nominalResistance; // Nominal resistance of the thermistor at 25°C
    float _seriesResistor; // Value of the series resistor used in the voltage divider
    float _beta; // Beta coefficient of the thermistor
public:
    void readTemperature(); // Method to read temperature from the thermistor
    Thermistor(uint8_t pinThermistor,float nominalResistance = 100000.0, float seriesResistor = 10000.0, float beta = 3950.0);

    void begin(); // Method to initialize the thermistor
    float getTemperature(); // Method to get the current temperature reading
};

#endif