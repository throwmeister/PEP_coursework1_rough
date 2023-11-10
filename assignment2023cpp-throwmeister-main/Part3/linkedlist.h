#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>
#include <initializer_list>
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
        head = nullptr;
        tail = nullptr;
        numOfElements = 0;
    }
    
    ~LinkedList(){
        for(int i=0; i<numOfElements; i++){
            Node<T>* t = head->next;
            delete head;
            head = t;
        }
        tail = nullptr;
        head = nullptr;
    }

    void push_front(const T &val){
        Node<T>* tmp = new Node<T>(val);
        if (head){
            tmp->next = head;
            head->previous = tmp;
            head = tmp;
            
        } else{
            head = tmp;
            tail = tmp;
        }
        numOfElements++;
    }

    T& front(){
        return head->data;
    }

    void push_back(const T &val){
        Node<T>* tmp = new Node<T>(val);
        if (tail){
            tmp->previous = tail;
            tail->next = tmp;
            tail = tmp;
        } else{
            head = tmp;
            tail = tmp;
        }
        numOfElements++;
    }

    T& back(){
        return tail->data;
    }

    const int size(){
        return numOfElements;
    }

    NodeIterator<T> begin(){
        NodeIterator<T> tmp(head);
        return tmp;
    }

    NodeIterator<T> end(){
        NodeIterator<T> nullIterator(nullptr);
        return nullIterator;
    }

    void reverse(){
        if(head){
            Node<T>* tmpPtr = nullptr;
            Node<T>* var = head->next;
            for(int i=0; i<numOfElements; i++){
                head->previous = head->next;
                head->next = tmpPtr;
                tmpPtr = head;
                head = head->previous;
            }
            tail = head;
            head = tmpPtr;
        }
    }
};



// do not edit below this line

#endif
