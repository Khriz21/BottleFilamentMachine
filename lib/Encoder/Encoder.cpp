#include "Encoder.h"

Encoder *Encoder::_instance = nullptr;
Encoder::Encoder(uint8_t clk, uint8_t dt, uint8_t sw)
    : pinCLK(clk), pinDT(dt), pinSW(sw)
{
    _instance = this;
}

//? <=====Iniciar Pines he interruptor de tiempo=====>
void Encoder::begin()
{
    pinMode(pinCLK, INPUT_PULLUP);
    pinMode(pinDT, INPUT_PULLUP);
    pinMode(pinSW, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(pinDT), isrMovement, FALLING);
    attachInterrupt(digitalPinToInterrupt(pinSW), isrSW, FALLING);
}

// ? <===== Detectar movimiento del encoder =====>

void Encoder::isrMovement()
{
    unsigned long now = micros();

    if (now - _instance->_lastInterrupTime < 1000) return;
    bool clkState = digitalRead(_instance->pinCLK);

    if (clkState == LOW)
        _instance->_position++;
    else
        _instance->_position--;

    _instance->_lastInterrupTime = now;
}

void Encoder::isrSW()
{
    unsigned long currentTime = millis();

    if (currentTime - _instance->_lastButtonPress > 200)
    {
        _instance->_buttonClicked = true;
        _instance->_lastButtonPress = currentTime;
    }
}

int32_t Encoder::getDelta()
{
    noInterrupts();
    int32_t tem = _position;
    _position = 0;
    interrupts();
    return tem;
}

bool Encoder::wasClicked()
{
    if (_instance->_buttonClicked)
    {
        _instance->_buttonClicked = false;
        return true;
    }

    return false;
}

void Encoder::reset()
{
    noInterrupts();
    _position = 0;
    interrupts();
}
