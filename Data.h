/*
Programmer: Zach Nett
Class: CptS 122; Lab Section 5
Programming Assignment: PA7
File: Data.h
Description: This program tracks attendance for a class, which can be viewed, modified, and have reports made based on.
*/

#pragma once

#include "PA7.h"
#include "Stack.h"

using std::string;
using std::ostream;

class Data {
public:
	//Default & Data Constructors, Destructor
	Data() : recordNumber(0), idNumber(0), name(""), email(""), units(""), major(""), level("") {}
    Data(int _record, int _id, string _name, string _email, string _units, string _major, string _level, int _numAbsences) : recordNumber(_record), idNumber(_id), name(_name), email(_email), units(_units), major(_major), level(_level), numAbsences(_numAbsences) {}
	~Data() {}
    
	//Overloaded assignment operator
	Data & operator= (Data &old) { 
		recordNumber = old.getRecord();
		idNumber = old.getID();
		name = old.getName();
		email = old.getEmail();
		units = old.getUnits();
		major = old.getMajor();
		level = old.getLevel();
		numAbsences = old.getNumAbsences();
		absenceInfo = old.getStack();
		return *this;
	}

    //Setters for data members (see problem description)
    void setRecord(int newRecord) { recordNumber = newRecord; }
    void setID(int newID) { idNumber = newID; }
    void setName(string newName) { name = newName; }
    void setEmail(string newEmail) { email = newEmail; }
    void setUnits(string newUnits) { units = newUnits; }
    void setMajor(string newMajor) { major = newMajor; }
    void setLevel(string newLevel) { level = newLevel; }
	void setNumAbsences(int newNum) { numAbsences = newNum; }
	void setStack(Stack newStack) { absenceInfo = newStack; }

    //Getters for data members (see problem description)
    int getRecord() { return recordNumber; }
    int getID() { return idNumber; }
    string getName() { return name; }
    string getEmail() { return email; }
    string getUnits() { return units; }
    string getMajor() { return major; }
    string getLevel() { return level; }
	int getNumAbsences() { return numAbsences; }
	Stack getStack() { return absenceInfo; }

	//Definition for overloaded stream insertion (see Data.cpp)
	friend ostream& operator<<(ostream &lhs, Data &rhs);

private:
    int recordNumber;
    int idNumber;
    string name;
    string email;
    string units;
    string major;
    string level;
	int numAbsences;
	Stack absenceInfo;
};