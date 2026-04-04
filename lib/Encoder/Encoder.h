#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder
{
private:
    uint8_t pinCLK;
    uint8_t pinDT;
    uint8_t pinSW;

    static Encoder *_instance;
    static void isrMovement();
    static void isrSW();

    volatile int32_t _position = 0;
    volatile bool _buttonClicked = false;
    volatile unsigned long _lastInterrupTime = 0;
    unsigned long _lastButtonPress = 0;

public:
    Encoder(uint8_t clk, uint8_t dt, uint8_t sw);

    void begin();

    int32_t getDelta();
    bool wasClicked();
    void reset();
};

#endif