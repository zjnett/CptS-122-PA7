/*
Programmer: Zach Nett
Class: CptS 122; Lab Section 5
Programming Assignment: PA7
File: main.cpp
Description: This program tracks attendance for a class, which can be viewed, modified, and have reports made based on.
*/

#include "PA7.h"
#include "LinkedList.h"
#include "Data.h"
#include "Menu.h"

using std::string;
using std::fstream;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;

int main(void) {
	Menu appMenu;
	LinkedList<Data> records;
	Status currentStatus = NOT_LOADED;

    time_t t = time(0);
    struct tm * now = localtime( & t );

	fstream infile;
    int selection = 0, subselection = 0;
    bool running = true;

	// Main Program Loop
    while (running) {
        appMenu.clearScreen();
        appMenu.printMenu(currentStatus);
        cin >> selection;
        switch(selection) {
            case 1: //Import course list
			{
				appMenu.clearScreen();
				char buffer[50] = { '\0' };
				char buffertwo[50] = { '\0' };
				int numProcessed = 1;
				infile.open("classList.csv");
				if (infile.is_open() && (currentStatus == NOT_LOADED || currentStatus == ERROR)) {
					for (int i = 0; i < 7; i++) {
						//ignore first line of file
						infile.getline(buffer, 50, ',');
					}
					while (!infile.eof()) {
						Data newRecord;
						//Set record information in order
						newRecord.setRecord(numProcessed++);
						infile.getline(buffer, 50, ',');
						newRecord.setID(atoi(buffer));
						infile.getline(buffer, 50, ',');
						infile.getline(buffertwo, 50, ',');
						strcat(buffer, ",");
						strcat(buffer, buffertwo);
						newRecord.setName(buffer);
						infile.getline(buffer, 50, ',');
						newRecord.setEmail(buffer);
						infile.getline(buffer, 50, ',');
						newRecord.setUnits(buffer);
						infile.getline(buffer, 50, ',');
						newRecord.setMajor(buffer);
						infile.getline(buffer, 50, ',');
						//Remove newline from buffer
						string processed = buffer;
						processed.erase(std::remove(processed.begin(), processed.end(), '\n'), processed.end());
						//Solution for removing non-alpha numeric characters from string using STL provided by "songyuanyao",
						//https://stackoverflow.com/questions/28491954/remove-non-alphabet-characters-from-string-c
						//Removes over-read characters after deleting newline. This is done to comply with the provided .csv file.
						processed.erase(std::remove_if(processed.begin(), processed.end(), [](char c) { return !isalpha(c); }), processed.end());
						newRecord.setLevel(processed);
						newRecord.setNumAbsences(0);

						//Insert student record into list
						records.insertAtFront(newRecord);
					}
					cout << "classList.csv imported successfully!" << endl;
					currentStatus = COURSE_LOADED;
				}
				else if (currentStatus != ERROR) {
					cout << "Error reading classList.csv - has it already been loaded?" << endl;
				}
				else {
					cout << "Error reading classList.csv. Is it in your program's directory?" << endl;
					currentStatus = ERROR;
				}
				infile.close();
				appMenu.systemPause();
				break;
			}
            case 2: //Load master list
			{
				appMenu.clearScreen();
				char buffer[50] = { '\0' };
				char buffertwo[50] = { '\0' };
				fstream masterfile;

				masterfile.open("master.txt");
				if (currentStatus == NOT_LOADED || currentStatus == ERROR && masterfile.is_open()) {
					int numProcessed = 1;
					//Skip initial item (numerator, which is instead processed internally)
					masterfile.getline(buffer, 50, ',');
					while (!masterfile.eof()) {
						Data newRecord;
						//Set record information in order
						newRecord.setRecord(numProcessed++);
						masterfile.getline(buffer, 50, ',');
						newRecord.setID(atoi(buffer));
						masterfile.getline(buffer, 50, ',');
						masterfile.getline(buffertwo, 50, ',');
						strcat(buffer, ",");
						strcat(buffer, buffertwo);
						newRecord.setName(buffer);
						masterfile.getline(buffer, 50, ',');
						newRecord.setEmail(buffer);
						masterfile.getline(buffer, 50, ',');
						newRecord.setUnits(buffer);
						masterfile.getline(buffer, 50, ',');
						newRecord.setMajor(buffer);
						masterfile.getline(buffer, 50, ',');
						newRecord.setLevel(buffer);
						masterfile.getline(buffer, 50, ',');
						newRecord.setNumAbsences(atoi(buffer));

						//Declare absences data structure before loop (prevent overwriting)
						Stack absences;
						int numIterations = newRecord.getNumAbsences();
						for (int i = 0; i < numIterations; i++) {
							//read in absences
							masterfile.getline(buffer, 50, ',');
							string processed = buffer;
							processed.erase(std::remove(processed.begin(), processed.end(), '\n'), processed.end());
							absences.push(processed);
							newRecord.setStack(absences);
						}
						records.insertAtFront(newRecord);
						//Read and ignore garbage newline
						masterfile.getline(buffer, 50, ',');
					}
					currentStatus = MASTER_LOADED;
					cout << "master.txt imported successfully!" << endl;
				}
				else if (currentStatus == COURSE_LOADED) {
					cout << "Error reading master.txt, classList.csv already loaded in this instance. Please restart." << endl;
				}
				else if (currentStatus == MASTER_LOADED) {
					cout << "Error reading master.txt, master.txt has already been loaded." << endl;
				}
				else {
					cout << "Error reading master.txt. Is it in your program's directory?" << endl;
					currentStatus = ERROR;
				}
				appMenu.systemPause();
				break;
			}
            case 3: //Store master list
			{
				appMenu.clearScreen();
				if (currentStatus == MASTER_LOADED || currentStatus == MASTER_MOD || currentStatus == COURSE_LOADED || currentStatus == MASTER_SAVED) { // at least one type of list is loaded
					fstream mastersave;
					mastersave.open("master.txt");
					int tracker = 1;
					if (mastersave.is_open()) {
						ListNode<Data> *temp = records.getHead();
						while (temp != nullptr) {
							Data currentRecord = temp->getData();
							mastersave << tracker++ << "," << currentRecord.getID() << "," << currentRecord.getName() << ","
								<< currentRecord.getEmail() << "," << currentRecord.getUnits() << "," << currentRecord.getMajor() << ","
								<< currentRecord.getLevel() << "," << currentRecord.getNumAbsences() << ",";
							if (currentRecord.getNumAbsences() > 0) {
								Stack tempStack = currentRecord.getStack();
								for (int i = 0; i < currentRecord.getNumAbsences(); i++) {
									mastersave << tempStack.peek() << ",";
									tempStack.pop();
									if (tempStack.isEmpty()) {
										mastersave << endl;
									}
								}
							} else {
								mastersave << endl;
							}
							temp = temp->getNext();
						}
						mastersave.close();
						currentStatus = MASTER_SAVED;
					}
				} else {
					cout << "Error - No current list loaded to store!" << endl;
				}
				break;
			}
            case 4: //Mark absences
			{
				//Print Records
				appMenu.clearScreen();
				if (currentStatus != ERROR && currentStatus != NOT_LOADED) {
					LinkedList<Data> tempList = records;
					ListNode<Data> *temp = tempList.getHead();
					while (temp != nullptr) {
						char in = '\0';
						cout << temp->getData().getRecord() << " - " << temp->getData().getName() << ": is this student absent today? [Y/N]: ";
						cin >> in;
						if (toupper(in) == 'Y') {
							Data current = temp->getData();
							int numA = current.getNumAbsences();
							current.setNumAbsences(numA + 1);
							string date = to_string((now->tm_year + 1900)) + "-" + to_string((now->tm_mon + 1)) + "-" + to_string(now->tm_mday);
							date.erase(std::remove(date.begin(), date.end(), '\n'), date.end());
							Stack absences = current.getStack();
							absences.push(date);
							current.setStack(absences);
							temp->setData(current);
						}
						temp = temp->getNext();
					}
					records = tempList;
					currentStatus = MASTER_MOD;
				}
				else {
					cout << "Error - Could not mark absences, do you have a list loaded?" << endl;
				}
				appMenu.systemPause();
				break;
			}
            case 5: //Generate report
			{
				appMenu.clearScreen();
				if (currentStatus != ERROR && currentStatus != NOT_LOADED) {
					appMenu.printSubMenu();
					cin >> subselection;
					if (subselection == 1) { // Generates a report with only the most recent absence
						appMenu.clearScreen();
						fstream absencesReport;
						absencesReport.open("absencesReport.txt");
						if (absencesReport.is_open()) {
							LinkedList<Data> tempList = records;
							ListNode<Data> *temp = tempList.getHead();
							while (temp != nullptr) {
								Stack absences = temp->getData().getStack();
								absencesReport << temp->getData().getName() << ", most recent absence: " << absences.peek() << endl;
								temp = temp->getNext();
							}
							cout << "Report written to absencesReport.txt successfully!" << endl;
							absencesReport.close();
						}
						else {
							cout << "Error - Cannot open absencesReport.txt for writing." << endl;
						}
					}
					else if (subselection == 2) { // Generates a report with absences that meet or exceed a number.
						appMenu.clearScreen();
						int atLeast = 0;
						fstream absencesExceeding;
						absencesExceeding.open("exceedingAbsencesReport.txt");
						if (absencesExceeding.is_open()) {
							cout << "Generate a report of students with at least how many absences?: ";
							cin >> atLeast;
							LinkedList<Data> tempList = records;
							ListNode<Data> *temp = tempList.getHead();
							absencesExceeding << "Students with Absences Exceeding " << atLeast << ":" << endl;
							while (temp != nullptr) {
								if (temp->getData().getNumAbsences() >= atLeast) {
									//Generate line on report for student
									absencesExceeding << temp->getData().getName() << endl;
								}
								temp = temp->getNext();
							}
							cout << "Report written to exceedingAbsencesReport.txt successfully!" << endl;
							absencesExceeding.close();
						}
						else {
							cout << "Error - Cannot open exceedingAbsencesReport.txt for writing." << endl;
						}
					}
					else {
						cout << "Error: Invalid selection." << endl;
					}
				}
				else {
					cout << "Error - Could not generate report, do you have a list loaded?" << endl;
				}
				appMenu.systemPause();
				break;
			}
            case 6: //Edit
			{
				appMenu.clearScreen();
				if (currentStatus != ERROR && currentStatus != NOT_LOADED) {
					int select = 0;
					bool found = false;
					cout << "Would you like to edit based on student name [1] or ID [2]? ";
					cin >> select;
					if (select == 1) {
						string last, first, name;
						cout << "What is the student's last name? ";
						cin >> last;
						cout << "What is the student's first name? ";
						cin >> first;
						name = "\"" + last + "," + first + "\"";

						//Linear search based on name
						//LinkedList<Data> tempList = records;
						ListNode<Data> *temp = records.getHead();
						while (temp != nullptr) {
							if (temp->getData().getName().compare(name) == 0) {
								//found at current node
								found = true;
								break;
							}
							temp = temp->getNext();
						}

						if (found) {
							string date;
							cout << temp->getData().getName() << " found..." << endl;
							if (temp->getData().getNumAbsences() > 0) {
								bool foundDate = false;
								cout << "What date was the student found to be present on? YYYY-M-D: ";
								cin >> date;
								Data currentData = temp->getData();
								Stack copy = temp->getData().getStack();
								Stack tempStack = temp->getData().getStack();
								while (!tempStack.isEmpty()) {
									if (tempStack.peek().compare(date) == 0) {
										foundDate = true;
										break;
									}
									tempStack.pop();
								}

								if (foundDate) {
									//Using stack, create a temporary list of dates except for the found, then reconstruct a stack.
									//Then replace the stack in the parent LinkedList with the new constructed stack.
									LinkedList<string> dateList;
									tempStack = copy; //reset tempStack
									while (!tempStack.isEmpty()) {
										if (tempStack.peek().compare(date) != 0) {
											dateList.insertAtFront(tempStack.peek());
										}
										tempStack.pop();
									}
									Stack newStack;
									ListNode<string> *dateListNode = dateList.getHead();
									while (dateListNode != nullptr) {
										string tempStr = dateListNode->getData();
										newStack.push(tempStr);
										dateListNode = dateListNode->getNext();
									}
									currentData.setStack(newStack);
									int n = temp->getData().getNumAbsences();
									currentData.setNumAbsences(n - 1);
									temp->setData(currentData);
									currentStatus = MASTER_MOD;
									cout << "Absence successfully removed!" << endl;
								}
								else {
									cout << "Could not find date that student was absent on!" << endl;
								}
							}
							else {
								char sel = '\0';
								cout << "However, there are no absences logged for this student." << endl;
								cout << "Would you like to log one? [Y/N] ";
								cin >> sel;
								if (toupper(sel) == 'Y') {
									cout << "What date was this student absent on? YYYY-M-D: ";
									cin >> date;
									int n = temp->getData().getNumAbsences();
									temp->getData().setNumAbsences(n + 1);
									Stack tempStack = temp->getData().getStack();
									tempStack.push(date);
									temp->getData().setStack(tempStack);
								}
							}
							currentStatus = MASTER_MOD;
							//records = tempList;
						}
						else {
							cout << "Student with a name of " << name << " could not be found." << endl;
						}
					}
					else if (select == 2) {
						int id;
						cout << "What is the student's ID? ";
						cin >> id;

						//Linear search based on ID
						LinkedList<Data> tempList = records;
						ListNode<Data> *temp = tempList.getHead();
						while (temp != nullptr) {
							if (temp->getData().getID() == id) {
								//found at current node
								found = true;
								break;
							}
							temp = temp->getNext();
						}

						if (found) {
							string date;
							cout << temp->getData().getName() << " found..." << endl;
							if (temp->getData().getNumAbsences() > 0) {
								bool foundDate = false;
								cout << "What date was the student found to be present on? YYYY-M-D: ";
								cin >> date;
								Data currentData = temp->getData();
								Stack copy = temp->getData().getStack();
								Stack tempStack = temp->getData().getStack();
								while (!tempStack.isEmpty()) {
									if (tempStack.peek().compare(date) == 0) {
										foundDate = true;
										break;
									}
									tempStack.pop();
								}

								if (foundDate) {
									//Using stack, create a temporary list of dates except for the found, then reconstruct a stack.
									//Then replace the stack in the parent LinkedList with the new constructed stack.
									LinkedList<string> dateList;
									tempStack = copy; //reset tempStack
									while (!tempStack.isEmpty()) {
										if (tempStack.peek().compare(date) != 0) {
											dateList.insertAtFront(tempStack.peek());
										}
										tempStack.pop();
									}
									Stack newStack;
									ListNode<string> *dateListNode = dateList.getHead();
									while (dateListNode != nullptr) {
										string tempStr = dateListNode->getData();
										newStack.push(tempStr);
										dateListNode = dateListNode->getNext();
									}
									currentData.setStack(newStack);
									int n = temp->getData().getNumAbsences();
									currentData.setNumAbsences(n - 1);
									temp->setData(currentData);
									currentStatus = MASTER_MOD;
									cout << "Absence successfully removed!" << endl;
								}
								else {
									cout << "Could not find date that student was absent on!" << endl;
								}
							}
							else {
								char sel = '\0';
								cout << "However, there are no absences logged for this student." << endl;
								cout << "Would you like to log one? [Y/N] ";
								cin >> sel;
								if (toupper(sel) == 'Y') {
									cout << "What date was this student absent on? YYYY-M-D: ";
									cin >> date;
									int n = temp->getData().getNumAbsences();
									temp->getData().setNumAbsences(n + 1);
									Stack tempStack = temp->getData().getStack();
									tempStack.push(date);
									temp->getData().setStack(tempStack);
								}
							}
							currentStatus = MASTER_MOD;
							//records = tempList;
						}
						else {
							cout << "Student with an ID of " << id << " could not be found." << endl;
						}
					}
					else {
						cout << "Error - Could not parse response." << endl;
					}
				}
				else {
					cout << "Error - Cannot edit absences of unloaded course! Please load master.txt or classList.csv first." << endl;
				}
				appMenu.systemPause();
				break;
			}
			case 7: //Exit
				running = false;
				break;
            default:
                break;
        }
    }
    return 0;
}