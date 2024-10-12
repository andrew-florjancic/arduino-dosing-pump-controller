//  Created by Andrew Florjancic on 10/12/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef ComingSoonMenuItem_h
#define ComingSoonMenuItem_h

#include <Arduino.h>
#include <MenuItem.h>

// A Menu item that displays a coming soon message for new features in development that will be released soon.
class ComingSoonMenuItem : public MenuItem {
    private:
        // The message displayed to the user.
        const String display_message = "Coming soon!";

        // Displays the display_message.
        void showFeature();

        // Required method, unused.
        void presentableWillDismiss();
        
        // Required method, unused.
        void leftAction();

        // Required method, unused.
        void rightAction();

        // Returns the user to the previous presentable
        void selectAction();
    public:

        // Constructor creates a ComingSoonMenuItem.
        // @param title: The title of the new feature.
        ComingSoonMenuItem(String title);
};
#endif
