/*
Programmer: Zach Nett
Class: CptS 122; Lab Section 5
Programming Assignment: PA7
File: ListNode.h
Description: This program tracks attendance for a class, which can be viewed, modified, and have reports made based on.
*/

#pragma once

#include "PA7.h"

//Template class for ListNode.
template <class T>
class ListNode {
public:
	//Generic Constructors & Destructor (default and value)
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