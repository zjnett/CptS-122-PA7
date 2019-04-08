#pragma once

#include "PA7.h"
#include "ListNode.h"

using std::cout;
using std::endl;

template <class T>
class LinkedList {
public:
    LinkedList() : head(nullptr) {}
	~LinkedList() {}

	bool isEmpty() {
		return head == nullptr;
	}

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
	
	ListNode<T> *getHead() { return head; }

	void setHead(ListNode<T> *newHead) { head = newHead; }

	/*void printList() {
		ListNode<T> *temp = head;
		while (temp->getNext() != nullptr) {
			cout << temp->getData() << ", " << endl;
		}
	}*/

private:
    ListNode<T> *head;
};