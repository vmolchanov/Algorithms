#ifndef node_hpp
#define node_hpp

class Node {
    
public:
    Node();
    
    Node(const int value);
    
    void setPrev(const Node *node);
    
    void setNext(const Node *node);
    
    Node* getPrev();
    
    Node* getNext();
    
    int getData();
    
private:
    int _data;
    Node *_prev;
    Node *_next;
};

#endif
