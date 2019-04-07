#pragma once

#include "PA7.h"

using std::string;

class Stack {
public:
	Stack();
	~Stack() {}

	bool push(string newAbsence);

	void pop();

	string peek();

	bool isEmpty();

private:
	string stackData[100];
};