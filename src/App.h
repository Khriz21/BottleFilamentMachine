#ifndef APP_H
#define APP_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "../include/PinConfig.h"
#include "Display.h"
#include "Menu.h"
#include "Encoder.h"
#include "MenuItem.h"
#include "Extruder.h"
#include "../lib/PIDController/PIDController.h"

class App
{
private:
    LiquidCrystal_I2C _lcd;
    Display _display;
    Menu _mainMenu;
    Encoder _encoder;
    Extruder _extruder;
    PIDController _pidController;

    enum AppMode
    {
        HOME_SCREEN,
        MAIN_MENU,
        SET_VALUES,
        TUNING_PID
    } _appMode;

    uint8_t _pidTuningIndex;
    bool _valueEditMode;
    int _lastDisplayTemp;

    MenuItem _motorItem;
    MenuItem _heaterItem;
    MenuItem _setTempItem;
    MenuItem _setSpeedItem;
    MenuItem _tuningPIDItem;
    MenuItem _exitItem;

    static App *_instance;

    void _handleUI();
    void _homeMode();
    void _menuMode();
    void _updatingValMode();
    void _tuningMode();

    static void onSetToggleMotor();
    static void onSetToggleHeater();
    static void onSetTemperature();
    static void onSetSpeed();
    static void onSetActionMenu();
    static void onSetExitMenu();

public:
    App();
    void begin();
    void run();
};

#endif
