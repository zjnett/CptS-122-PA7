#include "PA7.h"

using std::string;
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
    time_t t = time(0);
    struct tm * now = localtime( & t );

    int selection = 0, subselection = 0;
    bool running = true;

    while (running) {
        clearScreen();
        printMenu();
        cin >> selection;
        switch(selection) {
            case 1: //Import course list
                
                systemPause();
                break;
            case 2: //Load master list

                break;
            case 3: //Store master list

                break;
            case 4: //Mark absences

                break;
            case 5: //Generate report
                printSubMenu();
                cin >> subselection;
                if (subselection == 1) {

                } else if (subselection == 2) {

                } else {
                    cout << "Error: Invalid selection." << endl;
                }
                systemPause();
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

void printMenu() {
    cout << "1.    Import course list" << endl;
    cout << "2.    Load master list" << endl;
    cout << "3.    Store master list" << endl;
    cout << "4.    Mark absences" << endl;
    cout << "5.    Generate report" << endl;
    cout << "6.    Exit" << endl;
}

void printSubMenu() {
    cout << endl << "1. Generate report for all students; showing only the most recent absence for each student." << endl;
    cout << "2. Generate report for students with absences that match or exceed..." << endl;
}

//Cross Platform Clearscreen Support
void clearScreen() {
    //Print 100 newlines:
    cout << string(100, '\n');
    //Windows System Call:
    //system("cls");
}

void systemPause() {
    cin.ignore(1024, '\n');
    cout << "Press any key to continue..." << endl;
    cin.get();
    //Windows System Call:
    //system("pause");
}