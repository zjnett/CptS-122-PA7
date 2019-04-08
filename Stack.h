#pragma once

#include "PA7.h"

using std::string;
using std::vector;

class Stack {
public:
	Stack() {}
	~Stack() {}

	void push(string newAbsence);

	void pop();

	string peek();

	bool isEmpty();

private:
	vector<string> stackData;
};