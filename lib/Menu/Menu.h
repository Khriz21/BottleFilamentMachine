#include <Arduino.h>
#include "MenuItem.h"

#ifndef MENU_H
#define MENU_H
#define  MAX_MENU_ITEMS 6
class Menu
{
private:
    const char* _title;
    MenuItem* _items[MAX_MENU_ITEMS];
    uint8_t _itemCount;
    uint8_t _currentIndex;

public:
    Menu(const char* title);

    bool addItem(MenuItem* item);
    void navigate(int32_t delta);
    void select();
    const char* getTitle();
    MenuItem* getCurrentItem();
    MenuItem* getItem(uint8_t index);
    uint8_t getItemCount();           
    uint8_t getCurrentIndex(); 
};

#endif // Menu