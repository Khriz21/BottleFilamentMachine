#include "Display.h"

Display::Display(LiquidCrystal_I2C &lcd) : _lcd(lcd), _firstVisible(0), _needsUpdate(true), _height(2), _width(16) {}
void Display::begin()
{
    _lcd.init();
    _lcd.backlight();

    byte arrow[8] = {B00000,B00100,B00110,B11111,B00110,B00100,B00000,B00000};
    _lcd.createChar(0, arrow);
}

void Display::render(Menu &menu)
{
    
    uint8_t current = menu.getCurrentIndex();// integer division to find the first visible item index

    //? adjust _firstVisible to ensure current item is visible
    if (current < _firstVisible)
        _firstVisible = current;

    //? if current item is below the visible range, scroll down
    if(current >= _firstVisible + _height)
        _firstVisible = current - _height + 1;

    //? clear display
    for (uint8_t i = 0; i < _height; i++)
    {
        _lcd.setCursor(0, i);
        
        uint8_t itemIdx = _firstVisible + i;
        if (itemIdx >= menu.getItemCount()) break;

        MenuItem* item = menu.getItem(itemIdx);
        if(item == nullptr) break;

        String line = "";
        
        //? draw arrow
        if (itemIdx == current)
        {
            line += (char)0; // print arrow for current item
        }
        else
        {
            line += " "; // otherwise print space 
        }

        //? type-specific rendering

        switch (item->getType())
        {
        case MenuItem::ACTION:
            line += (char *)item->getLabel();
            break;
        case MenuItem::TOGGLE:
            line += (char *)item->getLabel();
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
}