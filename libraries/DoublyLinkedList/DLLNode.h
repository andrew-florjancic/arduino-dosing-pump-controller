//  Created by Andrew Florjancic on 9/18/24.
//  Copyright © 2024 Andrew Florjancic. All rights reserved
#ifndef DLLNode_h
#define DLLNode_h

// A Generic Doubly Linked List Node.
template <class T>
class DLLNode {
    public:
        // The data stored in the node.
        const T data;

        // A Pointer to the previous node in the list.
        DLLNode<T>* previous_node = nullptr;

        // A pointer to the next node in the list.
        DLLNode<T>* next_node = nullptr;

        // Constructor creates a DLLNode.
        // @param data: The data being stored in the DLLNode.
        DLLNode(T data);
};

template <class T>
DLLNode<T>::DLLNode(T data) : data(data) {}

#endif