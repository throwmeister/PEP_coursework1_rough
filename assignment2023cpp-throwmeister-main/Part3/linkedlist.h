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

    LinkedList(const std::initializer_list<T> initList){
        head = nullptr;
        tail = nullptr;
        numOfElements = initList.size();
        for(auto &num: initList){
            Node<T>* tmp = new Node<T>(num);
            if(head){
                tmp->previous = tail;
                tail->next = tmp;
                tail = tmp;
            } else{
                head = tmp;
                tail = tmp;
            }
        }
    }
    
    ~LinkedList(){
        // Only data that was created with new was each node
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

    T& front() const{
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

    T& back() const{
        return tail->data;
    }

    int size() const{
        return numOfElements;
    }

    NodeIterator<T> begin(){
        return NodeIterator<T>(head);
    }

    NodeIteratorConst<T> begin() const{
        return NodeIteratorConst<T>(head);
    }

    NodeIterator<T> end(){
        return NodeIterator<T>(nullptr);
    }

    NodeIteratorConst<T> end() const{
        return NodeIteratorConst<T>(nullptr);
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

    NodeIterator<T> insert(NodeIterator<T>& it, const T& val){
        Node<T>* tmp = new Node<T>(val);
        if(head){
            Node<T>* currNode = it.getCurrNode();
            if(currNode==head){
                currNode->previous = tmp;
                tmp->next = currNode;
                head = tmp;
            } else{ //[3,5,7], 4 at point 5
                Node<T>* prevNode = currNode->previous;
                // curNode = 5, prevNode = 3
                prevNode->next = tmp;
                currNode->previous = tmp;
                tmp->previous = prevNode;
                tmp->next = currNode;
            }

        } else{
            head = tmp;
            tail = tmp;
        }

        numOfElements++;
        return NodeIterator<T>(tmp);
    }

    NodeIterator<T> erase(NodeIterator<T>& it){
        Node<T>* currNode = it.getCurrNode();
        Node<T>* returnNode;

        if(numOfElements==1){
            // Case 0: one element list

            delete currNode;
            head = nullptr;
            tail = nullptr;
        } else if(currNode==head){
            // Case 1: erase element is the head of the list
            returnNode = currNode->next;

            delete currNode;
            returnNode->previous = nullptr;
            head = returnNode;
        } else if(currNode==tail){
            // Case 2: erase element is the tail of the list
            tail = currNode->previous;

            delete currNode;
            tail->next = nullptr;
            returnNode = nullptr;

        } else{
            // Case 3: erase element is inbetween
            Node<T>* prevNode = currNode->previous;
            returnNode = currNode->next;

            delete currNode;
            prevNode->next = returnNode;
            returnNode->previous = prevNode;
        }
        numOfElements--;
        return NodeIterator<T>(returnNode);
    }
};



// do not edit below this line

#endif
