/*
Programmer: Zach Nett
Class: CptS 122; Lab Section 5
Programming Assignment: PA7
File: LinkedList.h
Description: This program tracks attendance for a class, which can be viewed, modified, and have reports made based on.
*/

#pragma once

#include "PA7.h"
#include "ListNode.h"

using std::cout;
using std::endl;

//Template class for LinkedList.
template <class T>
class LinkedList {
public:
	//Constructor & Destructor (head otherwise initialized through insertion)
    LinkedList() : head(nullptr) {}
	~LinkedList() {}

	//Overloaded assignment operator
	LinkedList & operator= (LinkedList &old) {
		head = old.getHead();
		return *this;
	}

	//isEmpty function, determines if (this) list is empty
	bool isEmpty() {
		return head == nullptr;
	}

	//insertAtFront function, inserts data of type T into the list.
	bool insertAtFront(T data) {
		bool success = false;
		ListNode<T> *temp = new ListNode<T>(data);
		if (temp != nullptr) {
			success = true;
			temp->setNext(head);
			head = temp;
		}
		return success;
	}
	
	//Getter
	ListNode<T> *getHead() { return head; }

	//Setter
	void setHead(ListNode<T> *newHead) { head = newHead; }

private:
    ListNode<T> *head;
};