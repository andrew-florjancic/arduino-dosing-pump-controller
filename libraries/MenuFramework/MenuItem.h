//  Created by Andrew Florjancic on 9/18/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef MenuItem_h
#define MenuItem_h

#include <Presentable.h>
#include <Arduino.h>

// An item in a menu or a submenu in a supermenu.
class MenuItem : public Presentable {
    public:
        /* Type of MenuItem.
        *
        * `menu`: Presents a list of menu items to select from and will host a menu item when it is selected.
        * `item`: Presents its Feature and does not host any other Presentables.
        * `back`: Is a special non-functional MenuItem that when selected indicates to the menu that the menu should be dismissed.*/
        enum ItemType { menu, item, back };

        // The MenuItem's ItemType.
        const ItemType item_type;

        // The title of the item that will be displayed by the menu.
        const String title;

        // Constructor creates a MenuItem.
        // @param title: The title of the item.
        // @param item_type: The type of item.
        MenuItem(String title, ItemType item_type);
};

#endif