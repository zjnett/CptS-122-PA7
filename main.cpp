#include "PA7.h"
#include "LinkedList.h"
#include "Data.h"
#include "Menu.h"

using std::string;
using std::fstream;
using std::cout;
using std::cin;
using std::endl;

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
					while (!masterfile.eof()) {
						Data newRecord;
						//Set record information in order
						masterfile.getline(buffer, 50, ',');
						newRecord.setID(atoi(buffer));
						masterfile.getline(buffer, 50, ',');
						masterfile.getline(buffertwo, 50, ',');
						strcat(buffer, ", ");
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
						newRecord.setNumAbsences(0);
						records.insertAtFront(newRecord);
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
				if (currentStatus == MASTER_LOADED || currentStatus == MASTER_SAVED || currentStatus == COURSE_LOADED) { // at least one type of list is loaded

				}
				currentStatus = MASTER_SAVED;
				break;
			}
            case 4: //Mark absences
			{
				//Print Records
				appMenu.clearScreen();
				ListNode<Data> *temp = records.getHead();
				while (temp != nullptr) {
					cout << temp->getData().getRecord() << " - " << temp->getData().getName() << endl;
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