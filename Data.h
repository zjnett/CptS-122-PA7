#pragma once

using std::string;

class Data {
public:
    Data();
    Data(int _record, int _id, string _name, string _email, string _units, string _major, string _level) : recordNumber(_record), idNumber(_id), name(_name), email(_email), units(_units), major(_major), level(_level) {}
    ~Data();
    
    //Setters
    void setRecord(int newRecord) { recordNumber = newRecord; }
    void setID(int newID) { idNumber = newID; }
    void setName(string newName) { name = newName; }
    void setEmail(string newEmail) { email = newEmail; }
    void setUnits(string newUnits) { units = newUnits; }
    void setMajor(string newMajor) { major = newMajor; }
    void setLevel(string newLevel) { level = newLevel; }

    //Getters
    int getRecord() { return recordNumber; }
    int getID() { return idNumber; }
    string getName() { return name; }
    string getEmail() { return email; }
    string getUnits() { return units; }
    string getMajor() { return major; }
    string getLevel() { return level; }

private:
    int recordNumber;
    int idNumber;
    string name;
    string email;
    string units;
    string major;
    string level;
}