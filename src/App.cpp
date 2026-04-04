#include "App.h"

App *App::_instance = nullptr;

App::App()
    : _lcd(0x27, 16, 2),
      _display(_lcd),
      _mainMenu("Main Menu"),
      _encoder(EN_CLK, EN_DT, EN_SW),
      _extruder(),
      _pidController(3.0f, 0.5f, 0.05f, 0.0f, 255.0f),
      _appMode(HOME_SCREEN),
      _pidTuningIndex(0),
      _valueEditMode(false),
      _lastDisplayTemp(0),
      _motorItem("Motor", false, App::onSetToggleMotor),
      _heaterItem("Heater", false, App::onSetToggleHeater),
      _setTempItem("Set Temp", App::onSetTemperature),
      _setSpeedItem("Set Speed", App::onSetSpeed),
      _tuningPIDItem("Tuning PID", App::onSetActionMenu),
      _exitItem("Exit", App::onSetExitMenu)
{
    _instance = this;
    _mainMenu.addItem(&_motorItem);
    _mainMenu.addItem(&_heaterItem);
    _mainMenu.addItem(&_setTempItem);
    _mainMenu.addItem(&_setSpeedItem);
    _mainMenu.addItem(&_tuningPIDItem);
    _mainMenu.addItem(&_exitItem);
}

void App::begin()
{
    _display.begin();
    _encoder.begin();
    _extruder.begin();
}

void App::run()
{
    _extruder.update();
    _handleUI();
}

void App::_handleUI()
{
    switch (_appMode)
    {
    case HOME_SCREEN:
        _homeMode();
        break;
    case MAIN_MENU:
        _menuMode();
        break;
    case SET_VALUES:
        _updatingValMode();
        break;
    case TUNING_PID:
        _tuningMode();
        break;
    }
}

void App::_homeMode()
{
    int currentTemp = (int)_extruder.getCurrentTemperature();
    if (_lastDisplayTemp != currentTemp || _display.needsUpdate())
    {
        _display.showHomeScreen("Temp", "Speed",
                               _extruder.getTargetTemperature(),
                               currentTemp,
                               _extruder.getTargetSpeed());
        _lastDisplayTemp = currentTemp;
    }

    if (_encoder.wasClicked())
    {
        _appMode = MAIN_MENU;
        _display.setNeedsUpdate(true);
    }
}

void App::_menuMode()
{
    int32_t delta = _encoder.getDelta();

    if (_display.needsUpdate())
        _display.render(_mainMenu);

    if (delta != 0)
    {
        _mainMenu.navigate(delta);
        _display.setNeedsUpdate(true);
    }

    if (_encoder.wasClicked())
    {
        _mainMenu.select();
        _display.setNeedsUpdate(true);
    }
}

void App::_updatingValMode()
{
    int32_t delta = _encoder.getDelta();

    if (delta != 0)
    {
        if (_valueEditMode)
            _extruder.setTargetTemperature(constrain(_extruder.getTargetTemperature() + delta, 0, 300));
        else
            _extruder.setTargetSpeed(constrain(_extruder.getTargetSpeed() + delta, 0, 100));
        _display.setNeedsUpdate(true);
    }

    if (_encoder.wasClicked())
    {
        _appMode = MAIN_MENU;
        _display.setNeedsUpdate(true);
    }

    if (_display.needsUpdate())
    {
        char buffer[17];
        _lcd.clear();
        _lcd.setCursor(0, 0);
        if (_valueEditMode)
            snprintf(buffer, sizeof(buffer), "Temp: %d C", _extruder.getTargetTemperature());
        else
            snprintf(buffer, sizeof(buffer), "Speed: %d%%", _extruder.getTargetSpeed());
        _lcd.print(buffer);
        _lcd.setCursor(0, 1);
        _lcd.print("Click to exit");
    }
}

void App::_tuningMode()
{
    int32_t delta = _encoder.getDelta();

    if (delta != 0)
    {
        float kp = _pidController.getKp();
        float ki = _pidController.getKi();
        float kd = _pidController.getKd();

        if (_pidTuningIndex == 0)
            kp = constrain(kp + delta * 0.1f, 0.0f, 10.0f);
        else if (_pidTuningIndex == 1)
            ki = constrain(ki + delta * 0.01f, 0.0f, 5.0f);
        else
            kd = constrain(kd + delta * 0.001f, 0.0f, 1.0f);

        _pidController.setTunings(kp, ki, kd);
        _display.setNeedsUpdate(true);
    }

    if (_encoder.wasClicked())
    {
        if (_pidTuningIndex < 2)
            _pidTuningIndex++;
        else
        {
            _pidTuningIndex = 0;
            _appMode = MAIN_MENU;
        }
        _display.setNeedsUpdate(true);
    }

    if (_display.needsUpdate())
    {
        char buffer[17];
        _lcd.clear();
        _lcd.setCursor(0, 0);
        if (_pidTuningIndex == 0)
            snprintf(buffer, sizeof(buffer), "Kp: %.2f", (double)_pidController.getKp());
        else if (_pidTuningIndex == 1)
            snprintf(buffer, sizeof(buffer), "Ki: %.2f", (double)_pidController.getKi());
        else
            snprintf(buffer, sizeof(buffer), "Kd: %.3f", (double)_pidController.getKd());
        _lcd.print(buffer);
        _lcd.setCursor(0, 1);
        _lcd.print("Click next");
    }
}

void App::onSetToggleMotor()
{
    if (_instance)
        Serial.println(_instance->_motorItem.getState() ? "Motor ON" : "Motor OFF");
}

void App::onSetToggleHeater()
{
    if (_instance)
    {
        bool newState = !_instance->_heaterItem.getState();
        _instance->_heaterItem.setState(newState);
        _instance->_extruder.setHeaterEnabled(newState);
        Serial.println(newState ? "Heater ON" : "Heater OFF");
    }
}

void App::onSetTemperature()
{
    if (_instance)
    {
        _instance->_valueEditMode = true;
        _instance->_appMode = SET_VALUES;
        _instance->_display.setNeedsUpdate(true);
    }
}

void App::onSetSpeed()
{
    if (_instance)
    {
        _instance->_valueEditMode = false;
        _instance->_appMode = SET_VALUES;
        _instance->_display.setNeedsUpdate(true);
    }
}

void App::onSetActionMenu()
{
    if (_instance)
    {
        _instance->_pidTuningIndex = 0;
        _instance->_appMode = TUNING_PID;
        _instance->_display.setNeedsUpdate(true);
    }
}

void App::onSetExitMenu()
{
    if (_instance)
    {
        _instance->_appMode = (_instance->_appMode == TUNING_PID) ? MAIN_MENU : HOME_SCREEN;
        _instance->_display.setNeedsUpdate(true);
    }
}
