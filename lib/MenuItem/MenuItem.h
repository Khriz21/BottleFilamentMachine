#ifndef MENUITEM_H
#define MENUITEM_H

#include <Arduino.h>

typedef void (*MenuAction)();

class MenuItem
{
public:
    enum MenuItemType
    {
        ACTION,
        TOGGLE,
        VALUE
    };

private:
    const char *label;
    MenuAction action;
    bool toggleState = false;
    int *valuePtr;

    MenuItemType type;

public:
    MenuItem(const char *label, MenuAction function);
    MenuItem(const char *label, bool toggleState, MenuAction function);
    MenuItem(const char *label, int *valuePtr);

    void execute();
    void setState(bool state);
    bool getState();
    int getValue();
    const char *getLabel();
    MenuItemType getType();
};

#endif // MenuItem
