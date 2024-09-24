//  Created by Andrew Florjancic on 9/17/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef Presentable_h
#define Presentable_h

#include <Display.h>
#include <RotaryEncoder.h>
#include "Feature.h"

/*
 * A Presentable is a special type of Feature that can present its feature and also host other Presentables so they can present their own features.
 * There are five stages in the Presentable lifecycle.
 * 1: `Inactive`: All Presentables start their life here as they wait to be presented. Once a Presentable has been presented, it will transition to
 * the Presentation stage. Any action sent to an inactive Presentable will be ignored.
 * 2: `Presentation`: Is the main stage where the Presentable will present its Feature until it chooses to host another Presentable or is dismissed
 * when the feature is complete. If the Presentable opts to host a guest Presentable, then `host(Presentable* guest)` should be called which will
 * transition the Presentable to the Hosting stage and allow the guest to present. When the Feature is complete and ready to be dismissed,
 * `completePresentation()` should be called which will advance the Presentable to the Dismissing stage. Actions sent to the Presentable during the
 * Presentation stage will trigger one of the following Action methods to execute: `leftAction()`, `rightAction()`, `selectAction()`.
 * 3: `Hosting`: Is an optional stage where the Presentable acts as a host for another Presentable called the guest. Hosting a guest means that the
 * host will give control to the guest and allow the guest to present its own feature. Control will be returned to the host when the guest is
 * dismissed. During the Hosting stage, any Actions sent to the host will be transported to the guest that is presenting.
 * 4: `Dismissing`: Is the final stage in the Presentable lifecycle which allows the Presentable a chance to perform any last minute cleanup tasks in
 * `presentableWillDismiss()`. When a Presentable is dismissed, it will become inactive and wait until it is called to present again.
 * 5: `Error`: TODO: I'm not entirely sure I want to include this as a stage in the Presentable lifecycle. I think it fits better as part of a
 * Feature. Let's give this some more thought and revisit this later.
 */
class Presentable : public Feature {
    public:
        // Constructor creates a new Presentable.
        Presentable();

        // Sets the display and completion for the Presentable.
        // @param display: A pointer to the Display object that will be used to show features.
        // @param completion: A callback function that will be called when the Presentable is dismissed. This function should return control to the host
        void configurePresentable(Display* display, void (*completion)());

        // Sends an action to the Presentable.
        // @param action: The action being sent to the Presentable.
        void sendAction(RotaryEncoder::Actions action);

        // Starts the Presentable lifecycle or returns control to the Presentable after a guest is dismissed.
        void present();

    protected:
        // A pointer to a different Presentable that is being allowed to present itself by the current hosting Presentable.
        Presentable* guest;

        // Initiates the process of dismissing the Presentable. This needs to be called in one of the Action methods.
        void completePresentation();

        // True, if the Presentable is currently presenting, hosting another Presentable, or being dismissed.
        // A Presentable is still active while it is in the process of being dismissed, once fully dismissed it becomes inactive.
        bool isActive();

        // True if the Presentable is hosting another Presentable. When control is returned to the Presentable, then it is no longer hosting.
        bool isHosting();

        // Presents another Presentable, the guest, and yields control until the guest is dismissed.
        // @param guest: A pointer to the guest Presentable.
        void host(Presentable* guest);

        // This method is called after the Presentable is presented but before the first performance which provides an opportunity to start any background tasks.
        virtual void presentableWillPerform() {}

        // This method is called just before the Presentable is dismissed which provides an opportunity to perform any cleanup tasks to prepare for the next presentation. 
        virtual void presentableWillDismiss() = 0;

        // Executes code triggered by a left Action sent to the Presentable.
        virtual void leftAction() = 0;

        // Executes code triggered by a right Action sent to the Presentable.
        virtual void rightAction() = 0;

        // Executes code triggered by a select Action sent to the Presentable.
        virtual void selectAction() = 0;
    
    private:
        /*
        * Possible states the Presentable can be in.
        *
        * `inactive`: The Presentable is waiting to present.
        * `presenting`: The Presentable is activly presenting its feature or hosting another Presentable.
        * `dismissing`: The Presentable has finished presenting and is in the process of being dismissed.
        */
        enum PresentableState { inactive, presenting, dismissing };

        // The current state of the Presentable.
        PresentableState presentable_state = inactive;

        // A callback function that will be called when the Presentable is dismissed. This function has no paramaters and returns nothing. This
        // function should return control to the host.
        void (*completion)();

        // Determines which part of the presentation to execute based on the current state and calls the appropriate method. This method is always
        // called at the end of `present()` and will be called after an Action is completed.
        void perform();

        // Resets the presentation state to inactive and calls the completion function to return control to the host. Any Presentable being hosted
        // must be dismissed before the host Presentable can be dismissed. Calling `dismiss()` while activly hosting will do nothing.
        void dismiss();

        // Transports an action to the guest being presented.
        // @param action: The action to be sent to the guest.
        void transportAction(RotaryEncoder::Actions action);
};

#endif
