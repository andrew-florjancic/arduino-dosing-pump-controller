//  Created by Andrew Florjancic on 9/17/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#include "Presentable.h"

Presentable::Presentable() { }

void Presentable::perform() {
    if(isHosting()) { return; }
    switch(presentable_state) {
        case inactive: showError(1); break; // TODO: create some configuration method for the application to provide an error code to use
        case presenting: showFeature(); break;
        case dismissing: presentableWillDismiss(); dismiss(); break;
    }
}

void Presentable::completePresentation() {
    presentable_state = dismissing;
}

void Presentable::dismiss() {
    // TODO: Check isActive? seems incorrect to allow a call dismiss on an inactive Presentable. Look into this when we tackle disabling interrupts.
    if(isHosting()) { return; } // If a presentable is being hosted it must be dismissed first.
    presentable_state = inactive;
    completion();
}

void Presentable::configurePresentable(Display* display, void (*completion)()) {
    this->display = display;
    this->completion = completion;
}

void Presentable::present() {
    // TODO: We should probably check to ensure the Presentable isn't already presenting or is in the process of being dismissed. `present()` should
    // really only be called if inactive or hosting to start the lifecycle or return control, but it would be nice to have some sort of error
    // handling - do nothing or show an error code. Let's revisit this later.
    guest = nullptr;
    presentable_state = presenting;
    perform();
}

bool Presentable::isActive() {
    return presentable_state != inactive;
}

bool Presentable::isHosting() {
    return guest != nullptr;
}

void Presentable::inputCommand(Presentable::InputCommands command) {
     // TODO: It might be possible that inputCommand() gets called after a guest Presentable is set but before the guest has a chance to present due
     // to interrupts caused by input. Consider disabling interrupts during transitional states.
    if(!isActive()) { return; }
     // If hosting, then transport input commands to the guest.
    if(isHosting()) { transportCommand(command); return; }
    switch(command) {
        case left: leftAction(); break;
        case right: rightAction(); break;
        case select: selectAction(); break;
    }
    perform();
}

void Presentable::host(Presentable* guest) {
    if(!isActive() || isHosting()) { return; }
    this->guest = guest;
    guest->present();
}

void Presentable::transportCommand(Presentable::InputCommands command) { 
    guest->inputCommand(command);
}
