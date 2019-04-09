/*
Programmer: Zach Nett
Class: CptS 122; Lab Section 5
Programming Assignment: PA7
File: Stack.h
Description: This program tracks attendance for a class, which can be viewed, modified, and have reports made based on.
*/

#pragma once

#include "PA7.h"

using std::string;
using std::vector;

class Stack {
public:
	//Constructor and Destructor (vector implicitly initialized, reallocates dynamically)
	Stack() {}
	~Stack() {}

	//Push function based on vector used to track absence dates. O(1).
	void push(string newAbsence);

	//Pop function based on vector used to track absence dates. O(1).
	void pop();

	//Peek function based on vector used to track absence dates. O(1).
	string peek();

	//isEmpty helper function based on vector used to track absence dates. O(1).
	bool isEmpty();

private:
	vector<string> stackData;
};