#pragma once

#include "PA7.h"

template <class T>
class ListNode {
public:
	ListNode() : next(nullptr), nodeData() {}
	ListNode(T _nodeData) : nodeData(_nodeData) {}
	ListNode(ListNode *_next, T _nodeData) : next(_next), nodeData(_nodeData) {}
	~ListNode() {}

	//Setters
	void setNext(ListNode *newNext) { next = newNext; }
	void setData(T newData) { nodeData = newData; }

	//Getters
	ListNode *getNext() { return next;  }
	T getData() { return nodeData; }
private:
	ListNode *next;
	T nodeData;
};