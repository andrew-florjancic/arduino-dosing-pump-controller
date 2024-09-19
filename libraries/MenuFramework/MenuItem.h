//  Created by Andrew Florjancic on 9/18/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef MenuItem_h
#define MenuItem_h

#include <Presentable.h>
#include <Arduino.h>

// An item in a menu or a submenu in a supermenu.
class MenuItem : public Presentable {
    public:
        // True if the MenuItem is a return menu item. 
        const bool isReturnItem;

        // The title of the item that will be displayed by the menu.
        const String title;

        // Constructor creates a MenuItem.
        // @param title: The title of the item.
        // @param isReturnItem: True if the item is a return menu item.
        MenuItem(String title, bool isReturnItem);
};

#endif