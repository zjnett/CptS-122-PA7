#include "Stack.h"

using std::string;

Stack::Stack() {
	for (int i = 0; i < 100; i++) {
		stackData[i] = "";
	}
}

bool Stack::push(string newAbsence) {
	int i = 0;
	//Find end of the stack data
	while (stackData[i] != "") {
		i++;
	}
	int end = i;

	// Check if there is space in stack array
	if ((stackData + end + 1) == nullptr) {
		return false;
	}

	while (end >= 0) {
		stackData[end + 1] = stackData[end];
		end--;
	}

	stackData[0] = newAbsence;
	return true;
}

void Stack::pop() {
	//delete at front
	int i = 0;
	while (stackData[i + 1] != "" && i+1 < 100) {
		stackData[i] = stackData[i + 1];
		i++;
	}
}

string Stack::peek() {
	return stackData[0];
}

bool Stack::isEmpty() {
	if (stackData[0] == "" || stackData == nullptr) {
		return true;
	}
	return false;
}