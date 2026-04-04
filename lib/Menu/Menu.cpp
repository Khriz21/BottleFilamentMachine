#include "Menu.h"

Menu::Menu(const char *title)
{
    _title = title;
    _itemCount = 0;
    _currentIndex = 0;
     
}

bool Menu::addItem(MenuItem *item)
{
    if (_itemCount < MAX_MENU_ITEMS )
    {
        _items[_itemCount] = item;
        _itemCount++;
        return true;
    }
    
    return false; 
}

void Menu::navigate(int32_t delta)
{   if(_itemCount > 0) 
        _currentIndex = (_currentIndex + delta + _itemCount)%_itemCount;
}

void Menu::select()
{
    if(_itemCount == 0) return;
    MenuItem* selected = _items[_currentIndex];
    switch (selected->getType())
    {
    case MenuItem::ACTION:
        selected->execute();
        break;
    case MenuItem::TOGGLE:
        selected->setState(!selected->getState());
        selected->execute();
        break;
    case MenuItem::VALUE:
        selected->getValue();
        break;
    default:
        break;
    }
}

MenuItem *Menu::getItem(uint8_t index){
    if(index >= _itemCount) return nullptr;
    return _items[index];
}

MenuItem *Menu::getCurrentItem(){return _items[_currentIndex];}
const char *Menu::getTitle(){ return _title; }
uint8_t Menu::getItemCount() { return _itemCount; }
uint8_t Menu::getCurrentIndex(){ return _currentIndex; }
