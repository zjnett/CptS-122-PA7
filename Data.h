#pragma once

#include "PA7.h"
#include "Stack.h"

using std::string;
using std::ostream;

class Data {
public:
	Data() : recordNumber(0), idNumber(0), name(""), email(""), units(""), major(""), level("") {}
    Data(int _record, int _id, string _name, string _email, string _units, string _major, string _level, int _numAbsences) : recordNumber(_record), idNumber(_id), name(_name), email(_email), units(_units), major(_major), level(_level), numAbsences(_numAbsences) {}
	~Data() {}
    
	Data & operator= (Data &old) { 
		recordNumber = old.getRecord();
		idNumber = old.getID();
		name = old.getName();
		email = old.getEmail();
		units = old.getUnits();
		major = old.getMajor();
		level = old.getLevel();
	}

    //Setters
    void setRecord(int newRecord) { recordNumber = newRecord; }
    void setID(int newID) { idNumber = newID; }
    void setName(string newName) { name = newName; }
    void setEmail(string newEmail) { email = newEmail; }
    void setUnits(string newUnits) { units = newUnits; }
    void setMajor(string newMajor) { major = newMajor; }
    void setLevel(string newLevel) { level = newLevel; }
	void setNumAbsences(int newNum) { numAbsences = newNum; }

    //Getters
    int getRecord() { return recordNumber; }
    int getID() { return idNumber; }
    string getName() { return name; }
    string getEmail() { return email; }
    string getUnits() { return units; }
    string getMajor() { return major; }
    string getLevel() { return level; }
	int getNumAbsences() { return numAbsences; }

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