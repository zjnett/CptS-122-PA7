/*
Programmer: Zach Nett
Class: CptS 122; Lab Section 5
Programming Assignment: PA7
File: Stack.cpp
Description: This program tracks attendance for a class, which can be viewed, modified, and have reports made based on.
*/

#include "Stack.h"

using std::string;
using std::vector;

//Push function based on vector used to track absence dates. O(1).
void Stack::push(string newAbsence) {
	stackData.push_back(newAbsence);
}

//Pop function based on vector used to track absence dates. O(1).
void Stack::pop() {
	if (!isEmpty()) {
		stackData.pop_back();
	}
}

//Peek function based on vector used to track absence dates. O(1).
string Stack::peek() {
	if (stackData.size() > 0)
		return stackData.back();
	return "";
}

//isEmpty helper function based on vector used to track absence dates. O(1).
bool Stack::isEmpty() {
	return stackData.empty();
}