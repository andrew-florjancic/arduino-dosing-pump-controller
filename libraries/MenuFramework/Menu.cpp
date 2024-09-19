//  Created by Andrew Florjancic on 9/18/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved.
#include "Menu.h"

Menu::Menu(String title, DoublyLinkedList<MenuItem*>* menu) : MenuItem(title, false), menu(menu) {}

void Menu::addMenuItem(MenuItem* item, void (*completion)()) {
    item->configurePresentable(display, completion);
    menu->append(item);
}

void Menu::leftAction() {
   menu->previousItem();
}

void Menu::rightAction() {
    menu->nextItem();
}

void Menu::selectAction() {
    if(menu->current_item->data->isReturnItem) {
        completePresentation();
        return;
    }
    host(menu->current_item->data);
}

void Menu::returnControl() {
    present();
}

void Menu::showFeature() {
    display->lcd.clear();
    DLLNode<MenuItem*>* current_node = menu->current_item;
    for(uint8_t row = 0; row < display->rows; row++) {
        if(current_node == nullptr) { break; }
        display->lcd.setCursor(cursor.length(), row);
        display->lcd.print(current_node->data->title);
        current_node = current_node->next_node;
    }
    display->lcd.setCursor(0,0);
    display->lcd.print(cursor);
}

void Menu::presentableWillDismiss() {}
