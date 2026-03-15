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
    bool _needsUpdate;

public:
    Display(LiquidCrystal_I2C &lcd);

    void begin();
    void render(Menu &menu);
};

#endif