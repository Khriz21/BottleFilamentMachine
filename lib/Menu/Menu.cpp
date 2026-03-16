#include "Menu.h"

Menu::Menu(const char *title)
{
    this->title = title;
    this->itemCount = 0;
    this->currentIndex = 0;
     
}

bool Menu::addItem(MenuItem *item)
{
    if (this->itemCount < MAX_MENU_ITEMS )
    {
        this->items[this->itemCount] = item;
        this->itemCount++;
        return true;
    }
    
    return false; 
}

void Menu::navigate(int32_t delta)
{   if(this->itemCount > 0) 
        this->currentIndex = (currentIndex + delta + this->itemCount)%this->itemCount;
}

void Menu::selec()
{
    if(this->itemCount == 0) return;
    MenuItem* selected = this->items[this->currentIndex];
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
    if(index >= this->itemCount) return nullptr;
    return this->items[index];
}

MenuItem *Menu::getCurrentItem(){return this->items[this->currentIndex];}
const char *Menu::getTitle(){ return this->title; }
uint8_t Menu::getItemCount() { return this->itemCount; }
uint8_t Menu::getCurrentIndex(){ return this->currentIndex; }
