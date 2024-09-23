//  Created by Andrew Florjancic on 9/18/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "DLLNode.h"

// A Generic Doubly Linked List.
template <class T> 
class DoublyLinkedList {
    private:
        DLLNode<T>* head = nullptr; // A pointer to the first item in the list.
        DLLNode<T>* tail = nullptr; // A pointer to the last item in the list.
        DLLNode<T>* current_item = nullptr; // A pointer to the current item in the list.
    public:
        // Constructor creates an empty DoublyLinkedList. 
        DoublyLinkedList();

        // Returns a pointer to the current item.
        DLLNode<T>* getCurrentItem();

        // Returns a pointer to the first item in the list.
        DLLNode<T>* getHead();

        // Returns a pointer to the last item in the list.
        DLLNode<T>* getTail();

        // Sets the current item to the next item if one exists.
        void nextItem();

        // Sets the current item to the previous item if one exists.
        void previousItem();

        // Appends a new node containing the provided data to the end of the list and sets the current item to the head of the list.
        // @param data: The new data to append to the list.
        void append(T data);

        // Traverses the list from the head to the tail and sets the current item to the item that contains the provided data. If none of the items
        // in the list contains the data then the current item will be set to the last item in the list.
        // @param data: The value of the item that should be set to the current item.
        void setCurrentItem(T data);

};

template <class T> 
DoublyLinkedList<T>::DoublyLinkedList() { }

template <class T> 
DLLNode<T>* DoublyLinkedList<T>::getCurrentItem() {
    return current_item;
}

template <class T> 
DLLNode<T>* DoublyLinkedList<T>::getHead() {
    return head;
}

template <class T> 
DLLNode<T>* DoublyLinkedList<T>::getTail() {
    return tail;
}

template <class T> 
void DoublyLinkedList<T>::nextItem() {
    if(current_item == nullptr) { return; } 
    if(current_item->next_node == nullptr) { return; }
    current_item = current_item->next_node;
}

template <class T> 
void DoublyLinkedList<T>::previousItem() {
    if(current_item == nullptr) { return; }
    if(current_item->previous_node == nullptr) { return; }
    current_item = current_item->previous_node;
} 

template <class T> 
void DoublyLinkedList<T>::append(T data) {
    DLLNode<T>* newNode = new DLLNode<T>(data);
    if(head == nullptr || tail == nullptr) {
        // List is empty
        head = newNode;
    } else {
        // List has at least one item
        newNode->previous_node = tail;
        tail->next_node = newNode;
    }
    tail = newNode;
    current_item = head;
}

template <class T> 
void DoublyLinkedList<T>::setCurrentItem(T data) {
    if(head == nullptr) { return; }
    current_item = head;
    while(current_item->next_node != nullptr) {
        if(current_item->data == data) { break; }
        nextItem();
    }
}
#endif
