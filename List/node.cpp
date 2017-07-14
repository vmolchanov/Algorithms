#include "node.h"


Node::Node() : _data(0), _prev(nullptr), _next(nullptr) {}


Node::Node(const int value) : _data(value), _prev(nullptr), _next(nullptr) {}


void Node::setPrev(const Node *node) {
    _prev = const_cast<Node*>(node);
}


void Node::setNext(const Node *node) {
    _next = const_cast<Node*>(node);
}


Node* Node::getPrev() {
    return _prev;
}


Node* Node::getNext() {
    return _next;
}


int Node::getData() {
    return _data;
}

