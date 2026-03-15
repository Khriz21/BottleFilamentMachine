#include "Display.h"

Display::Display(LiquidCrystal_I2C &lcd) : _lcd(lcd), _needsUpdate(true) {}

void Display::begin()
{
    _lcd.init();
    _lcd.backlight();
    byte arrow[8] = {B00000, B00100, B01110, B11111, B01110, B00100, B00000, B00000};
    _lcd.createChar(0, arrow);
}

void Display::render(Menu &menu)
{
    // const uint8_t width = 16;
    const uint8_t height = 2;
    _lcd.setCursor(0, 0);

    // clear display
    for (uint8_t i = 0; i < height; i++)
    {
        _lcd.setCursor(0, i);
        
        uint8_t itemIdx = (menu.getCurrentIndex() + i) % menu.getItemCount();
        MenuItem *item = menu.getItem(itemIdx);
        if (item == nullptr) break;

        String line = "";
        

        if (itemIdx == menu.getCurrentIndex())
            line += (char)0; // print arrow for current item
        else
            line += " "; // otherwise print space

        switch (item->getType())
        {
        case MenuItem::ACTION:
            line += (char *)item->getLabel();
            break;
        case MenuItem::TOGGLE:
            line += (char *)item->getLabel();
            line += item->getState() ? " [ON]" : " [OFF]";
            break;
        case MenuItem::VALUE:
            line += (char *)item->getLabel();
            line += item->getValue();
            break;
        }
        _lcd.print(line);
        // pad with spaces to clear any leftover characters from previous render
        for(uint8_t j = line.length(); j < 16; j++) _lcd.print(" ");  
    }
}