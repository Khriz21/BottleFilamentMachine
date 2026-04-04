#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Menu.h"

class Display
{
private:
    LiquidCrystal_I2C &_lcd;
    uint8_t _firstVisible;
    bool _needsUpdate;
    const uint8_t _height;
    const uint8_t _width;

public:
    Display(LiquidCrystal_I2C &lcd);

    void begin();
    void render(Menu &menu);
    void showHomeScreen(const char* TLabel, const char* mLavel, uint8_t setTemp, int16_t curTemp, uint8_t setSpeed);
    void setNeedsUpdate(bool needsUpdate);
    bool needsUpdate();
};

#endif