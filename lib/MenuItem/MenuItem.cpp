#include "MenuItem.h"

MenuItem::MenuItem(const char *label, MenuAction function)
{
    this->label = label;
    this->action = function;
    this->valuePtr = nullptr;
    this->type = MenuItemType::ACTION;
}

MenuItem::MenuItem(const char *label, bool toggleState, MenuAction function)
{
    this->label = label;
    this->toggleState = toggleState;
    this->action = function;
    this->valuePtr = nullptr;
    this->type = MenuItemType::TOGGLE;
}

MenuItem::MenuItem(const char *label, int *valuePtr)
{
    this->label = label;
    this->valuePtr = valuePtr;
    this->action = nullptr;
    this->type = MenuItemType::VALUE;
}

void MenuItem::execute()
{
    if (action != nullptr)
        action();
}

void MenuItem::setState(bool state)
{
    this->toggleState = state;
}

bool MenuItem::getState()
{
    return this->toggleState;
}

int MenuItem::getValue()
{
    return *this->valuePtr;
}

const char *MenuItem::getLabel()
{
    return this->label;
}

MenuItem::MenuItemType MenuItem::getType()
{
    return this->type;
}
