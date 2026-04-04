#include "Display.h"

Display::Display(LiquidCrystal_I2C &lcd) : _lcd(lcd), _firstVisible(0), _height(2), _width(16) {}
void Display::begin()
{
    _lcd.init();
    _lcd.backlight();
    _needsUpdate = true;
    
    byte arrow[8] = {B00000,B00100,B00110,B11111,B00110,B00100,B00000,B00000};
    
    _lcd.createChar(0, arrow);
}

void Display::setNeedsUpdate(bool needsUpdate){_needsUpdate = needsUpdate;}
bool Display::needsUpdate(){return _needsUpdate;}

void Display::render(Menu &menu)
{
    //? Get the index of the currently selected item
    uint8_t current = menu.getCurrentIndex();

    //? adjust _firstVisible to ensure current item is visible
    if (current < _firstVisible)
        _firstVisible = current;

    //? if current item is below the visible range, scroll down
    if(current >= _firstVisible + _height)
        _firstVisible = current - _height + 1;

    //? Render visible items
    for (uint8_t i = 0; i < _height; i++)
    {
        _lcd.setCursor(0, i);
        
        uint8_t itemIdx = _firstVisible + i;
        if (itemIdx >= menu.getItemCount()) break;

        MenuItem* item = menu.getItem(itemIdx);
        if(item == nullptr) break;

        String line = "";
        
        //? draw arrow if this is the current item
        if (itemIdx == current)
        {
            line += (char)0;
        }
        else
        {
            line += " "; 
        }

        //? type-specific rendering

        switch (item->getType())
        {
        case MenuItem::ACTION:
            line += (char *)item->getLabel();
            break;
        case MenuItem::TOGGLE:
            line += (char *)item->getLabel();
            line += ": ";     
            line += item->getState() ? " ON" : " OFF";
            break;
        case MenuItem::VALUE:
            line += (char *)item->getLabel();
            line += ": ";
            line += item->getValue();
            break;
        }
        _lcd.print(line);
        // pad with spaces to clear any leftover characters from previous render
        for(uint8_t j = line.length(); j < _width; j++) _lcd.print(" ");
    }
    _needsUpdate = false;  
}

void Display::showHomeScreen(const char* TLabel, const char* mLavel, uint8_t setTemp, int16_t curTemp, uint8_t setSpeed)
{
    char buffer[17];
    snprintf(buffer, sizeof(buffer),"%s: %d/%dC",TLabel, setTemp, (int)curTemp);
    _lcd.setCursor(0, 0);
    _lcd.print(buffer);
    snprintf(buffer, sizeof(buffer), "%s: %d%%",mLavel, setSpeed);
    _lcd.setCursor(0, 1);
    _lcd.print(buffer);
    _needsUpdate = false;
}

