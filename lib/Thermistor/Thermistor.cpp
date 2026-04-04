#include "Thermistor.h"

Thermistor::Thermistor(uint8_t pinThermistor, float nominalResistance, float seriesResistor, float beta)
    : _pinThermistor(pinThermistor),
      _interval(200), // Change interval to 200 ms for better PID responsiveness
      _nominalResistance(nominalResistance), // Assuming a 100k ohm thermistor at 25°C
      _seriesResistor(seriesResistor), // Default series resistor value (10k ohms)
      _beta(beta) // Default beta value for a common NTC thermistor

{
    _temperature = 0.0;   
    _ntcResistance = 0.0;
    _voltage = 0.0;
}

void Thermistor::begin()
{
    pinMode(_pinThermistor, INPUT);
    // Realizar una lectura forzada inicial
    _lastReadTime = millis() - _interval; 
    readTemperature(); 
}


void Thermistor::readTemperature()
{
    _currentTime = millis();
    // Only read temperature if the specified interval has passed
    if (_currentTime - _lastReadTime >= _interval)
    {
        _lastReadTime = _currentTime; // Update last read time
        
        _voltage = analogRead(_pinThermistor) * (5.0 / 1023.0); // Convert ADC value to voltage

        _ntcResistance = (5.0 - _voltage) * _seriesResistor / _voltage; // Calculate resistance using voltage divider formula
        
        // Calculate temperature using the Steinhart-Hart equation
        float steinhart;
        steinhart = log(_ntcResistance / _nominalResistance); // ln(R/R0)
        steinhart /= _beta;                        // 1/B * ln(R/R0)
        steinhart += 1.0 / (25.0 + 273.15);         // + (1/T0)
        steinhart = 1.0 / steinhart;                // Invert to get temperature in Kelvin
        _temperature = steinhart - 273.15;          // Convert to Celsius
    }
}
float Thermistor::getTemperature(){ return _temperature; }