#include "PIDController.h"

PIDController::PIDController(float kp, float ki, float kd, float minOutput, float maxOutput) 
    : _kp(kp),
     _ki(ki),
     _kd(kd), 
     _minOutput(minOutput),
     _maxOutput(maxOutput)
{
    _setpoint = 0.0;
    _integral = 0.0;
    _lastError = 0.0;
    _output = 0.0;
}

void PIDController::setSetpoint(float sp) { this->_setpoint = sp; }

void PIDController::setTunings(float kp, float ki, float kd) {
    _kp = kp;
    _ki = ki;
    _kd = kd;
}

float PIDController::compute(float input, float dt)
{   
    if (dt <= 0.0f) return _output; 
    float error = _setpoint - input;
    
    // Calcular integral pero previniendo crecimiento infinito (Anti-Windup)
    _integral += error * dt;

    // Clamping para limitar el término integral y evitar windup
    if (_ki > 0.0f) { // Prevenir división por cero si _ki es 0
        if (_ki * _integral > _maxOutput) _integral = _maxOutput / _ki;
        else if (_ki * _integral < _minOutput) _integral = _minOutput / _ki;
    }

    float derivative = (error - _lastError) / dt;

    this->_output = (_kp * error) + (_ki * _integral) + (_kd * derivative);
    
    // Clamp output final to min/max limits
    if (_output > _maxOutput) {
        _output = _maxOutput;
    } else if (_output < _minOutput) {
        _output = _minOutput;
    }

    _lastError = error;
    return _output;
}
