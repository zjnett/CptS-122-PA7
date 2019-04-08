#include "Stack.h"

using std::string;
using std::vector;

void Stack::push(string newAbsence) {
	stackData.push_back(newAbsence);
}

void Stack::pop() {
	if (!isEmpty()) {
		stackData.pop_back();
	}
}

string Stack::peek() {
	return stackData.back();
}

bool Stack::isEmpty() {
	return stackData.empty();
}