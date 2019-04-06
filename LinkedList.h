#pragma once

template <class T>
class LinkedList {
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList();

    bool push();
    bool pop();
    Data peek();
    bool isEmpty();
private:
    T *head;
}