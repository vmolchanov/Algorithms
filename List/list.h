#ifndef list_hpp
#define list_hpp

#include "node.h"

class List {
    
public:
    List();
    List(const int value);
    
    void pushBack(const int value);
    void pushFront(const int value);
    int popBack();
    int popFront();
    
    bool isEmpty() const {
        return _isEmpty;
    }
    
private:
    Node *_node;
    Node *_head;
    Node *_tail;
    
    bool _isEmpty;
};

#endif /* list_hpp */
