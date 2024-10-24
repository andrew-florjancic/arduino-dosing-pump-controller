//  Created by Andrew Florjancic on 9/18/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef Menu_h
#define Menu_h

#include <Arduino.h>
#include <DoublyLinkedList.h>
#include "MenuItem.h"

// A Menu of MenuItems that is itself a MenuItem so it can also be in a Menu.
class Menu: public MenuItem {
    public:
        // Constructor creates a menu.
        // @param: title: The title of the menu that will be used if this menu is part of another menu.
        Menu(String title);

        // Returns control to the menu after one of its guests dismisses themselves.
        void returnControl();

        // Adds the MenuItem to the menu and configures the item.
        // @param item: The new item to add to the menu.
        // @aram completion: A callback function that should return control to the menu when the menu item is dismissed.
        void addMenuItem(MenuItem* item, void (*completion)());
    protected:
        // Displays the menu starting from the menu's current item.
        void showFeature();

        // Updates the current item in the menu to the previous item in the menu
        void leftAction() override;

        // Updates the current item in the menu to the previous item in the menu.
        void rightAction() override;

        // Displays the current item or dismisses the current menu if the current item's ItemType is back.
        void selectAction();
    private:
        // An indicator that points to the current item in the menu.
        const String cursor = "-> ";

        // A list containing items that the user can select and display.
        DoublyLinkedList<MenuItem*> menu = DoublyLinkedList<MenuItem*>();
};

#endif