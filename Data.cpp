/*
Programmer: Zach Nett
Class: CptS 122; Lab Section 5
Programming Assignment: PA7
File: Data.cpp
Description: This program tracks attendance for a class, which can be viewed, modified, and have reports made based on.
*/

#include "Data.h"

//Overloaded stream insertion operator for Data type
ostream& operator<<(ostream &lhs, Data &rhs) {
	lhs << rhs.getName();
	return lhs;
}