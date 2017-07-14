#include "list.h"


List::List() {
    _node = new Node;
    
    _head = _node;
    _tail = _node;
    
    _isEmpty = true;
}


List::List(const int value) {
    _node = new Node(value);
    
    _head = _node;
    _tail = _node;
    
    _isEmpty = false;
}


void List::pushBack(const int value) {
    Node *nd = new Node(value);
    
    if (isEmpty()) {
        _node = nd;
        _isEmpty = false;
    } else {
        nd->setPrev(_tail);
        
        _tail->setNext(nd);
        _tail = nd;
    }
}


void List::pushFront(const int value) {
    Node *nd = new Node(value);
    
    if (isEmpty()) {
        _node = nd;
        _isEmpty = false;
    } else {
        nd->setNext(_head);
        
        _head->setPrev(nd);
        _head = nd;
    }
}


int List::popBack() {
    if (isEmpty()) {
        return 0;
    }
    
    int value = _tail->getData();
    
    if (_head != _tail) {
        _tail = _tail->getPrev();
        delete _tail->getNext();
        _tail->setNext(nullptr);
    } else {
        _isEmpty = true;
    }
    
    return value;
}


int List::popFront() {
    if (isEmpty()) {
        return 0;
    }
    
    int value = _head->getData();
    
    if (_head != _tail) {
        _head = _head->getNext();
        delete _head->getPrev();
        _head->setPrev(nullptr);
    } else {
        _isEmpty = true;
    }
    
    return value;
}
