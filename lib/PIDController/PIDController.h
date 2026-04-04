#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PIDController {
private:
    float _kp;           // Proportional gain
    float _ki;           // Integral gain
    float _kd;           // Derivative gain
    float _setpoint;     // Target value
    float _integral;     // Accumulated integral term
    float _lastError;    // Previous error
    float _output;       // PID output
    float _minOutput;    // Minimum output limit
    float _maxOutput;    // Maximum output limit

public:
    PIDController(float kp = 1.00, float ki = 0.00, float kd = 0.00, float minOutput = -255, float maxOutput = 255);
    void setSetpoint(float sp);
    float compute(float input, float dt);
    void setTunings(float kp, float ki, float kd);

    // Getters para los parámetros PID
    float getKp() const { return _kp; }
    float getKi() const { return _ki; }
    float getKd() const { return _kd; }
};

#endif