#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:

template<typename T>
class LinkedList {

private:
    Node<T>* head;
    Node<T>* tail;
    int numOfElements;

public:
    LinkedList(){

    }

    ~LinkedList(){

    }

    void push_front(T &val){

    }

    T& front(){
        return head->data;
    }

    void push_back(T &val){

    }

    T& back(){
        return tail->data;
    }

    int size(){
        return numOfElements;
    }

    NodeIterator<T>& begin(){
        tmp = NodeIterator<T>(head);
        return tmp;
    }

    NodeIterator<T>& end(){
        return tail->next;
    }

    void reverse(){
        
    }
};



// do not edit below this line

#endif
