#pragma once

template <class T>
class LinkedList {
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList();

    
private:
    T *head;
}