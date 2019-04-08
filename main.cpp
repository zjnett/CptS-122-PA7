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

/* Code to get current time:
(assuming struct and t have been declared)
    cout << (now->tm_year + 1900) << '-'
    << (now->tm_mon + 1) << '-'
    << now->tm_mday
    << endl;
*/

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
						strcat(buffer, ", ");
						strcat(buffer, buffertwo);
						newRecord.setName(buffer);
						infile.getline(buffer, 50, ',');
						newRecord.setEmail(buffer);
						infile.getline(buffer, 50, ',');
						newRecord.setUnits(buffer);
						infile.getline(buffer, 50, ',');
						newRecord.setMajor(buffer);
						infile.getline(buffer, 50, ',');
						newRecord.setLevel(buffer);
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
				ListNode<Data> *temp = records.getHead();
				while (temp != nullptr) {
					char in = '\0';
					cout << temp->getData().getRecord() << " - " << temp->getData().getName()  << ": is this student absent today? [Y/N]: ";
					cin >> in;
					if (toupper(in) == 'Y') {
						Data current = temp->getData();
						int numA = current.getNumAbsences();
						current.setNumAbsences(numA + 1);
						string date = to_string((now->tm_year + 1900)) + "-" + to_string((now->tm_mon + 1)) + "-" + to_string(now->tm_mday);
						current.getStack().push(date);
						temp->setData(current);
					}
					temp = temp->getNext();
				}
				currentStatus = MASTER_MOD;
				appMenu.systemPause();
				break;
			}
            case 5: //Generate report
				appMenu.clearScreen();
                appMenu.printSubMenu();
                cin >> subselection;
                if (subselection == 1) {

                } else if (subselection == 2) {

                } else {
                    cout << "Error: Invalid selection." << endl;
                }
                appMenu.systemPause();
                break;
            case 6: //Exit
                running = false;
                break;
            default:
                break;
        }
    }

    return 0;
}