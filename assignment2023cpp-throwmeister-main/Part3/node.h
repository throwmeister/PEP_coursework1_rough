#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please email me
// TODO your code for the Node class goes here:
// (Note the 'NodeIterator' class will report lots of errors until Node exists)

template<typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* previous;

    Node(T inpData): data(inpData){
        next = nullptr;
        previous = nullptr;
    }
};

template<typename T>
class NodeIterator {
  
private:
    Node<T>* current;
    
public:
    NodeIterator(Node<T>* currentIn)
        : current(currentIn) {        
    }

    T& operator*() {
        return current->data;
    }

    void operator++(){
        current = current->next;
    }

    bool operator==(const NodeIterator<T> &other){
        if(current==other.current){
            return true;
        }
        return false;
    }

    bool operator!=(const NodeIterator<T> &other){
        if(current==other.current){
            return false;
        }
        return true;
    }

    Node<T>* getCurrNode(){
        return current;
    }
    // TODO: complete the code for NodeIterator here
        
};

// do not edit below this line

#endif
