//  Created by Andrew Florjancic on 9/22/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef ReturnMenuItem_h
#define ReturnMenuItem_h

#include <MenuItem.h>

// A special MenuItem only used by a Menu to return control to the supermenu. This item should never actually be presented.
class ReturnMenuItem : public MenuItem {
    private:
        // Empty method, should never actually be executed
        void showFeature();

        // Empty method, should never actually be executed
        void selectAction(); 
    public:
        // Constructor creates a ReturnMenuItem.
        ReturnMenuItem();
};
#endif
