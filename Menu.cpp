/*
Programmer: Zach Nett
Class: CptS 122; Lab Section 5
Programming Assignment: PA7
File: Menu.cpp
Description: This program tracks attendance for a class, which can be viewed, modified, and have reports made based on.
*/

#include "Menu.h"

using std::cout;
using std::endl;
using std::cin;

//printMenu function to print menu art and options.
//As usual, ASCII art generated on patorjk.
void Menu::printMenu(Status currentStatus) {
	//cout << "\u001b[34;1m" << endl; // Bright Blue
	colorPicker(currentStatus);
	cout << "    ###    ######## ######## ######## ##    ## ########     ###    ##    ##  ######  ########" << endl;
	cout << "   ## ##      ##       ##    ##       ###   ## ##     ##   ## ##   ###   ## ##    ## ##" << endl;
	cout << "  ##   ##     ##       ##    ##       ####  ## ##     ##  ##   ##  ####  ## ##       ##" << endl;
	cout << " ##     ##    ##       ##    ######   ## ## ## ##     ## ##     ## ## ## ## ##       ######" << endl;
	cout << " #########    ##       ##    ##       ##  #### ##     ## ######### ##  #### ##       ##" << endl;
	cout << " ##     ##    ##       ##    ##       ##   ### ##     ## ##     ## ##   ### ##    ## ##" << endl;
	cout << " ##     ##    ##       ##    ######## ##    ## ########  ##     ## ##    ##  ######  ########" << endl;
	cout << "\u001b[0m" << endl; // Reset
	cout << "    (implementation by Zach Nett)" << endl << endl;
    cout << "\t1.    Import course list" << endl << endl;
    cout << "\t2.    Load master list" << endl << endl;
    cout << "\t3.    Store master list" << endl << endl;
    cout << "\t4.    Mark absences" << endl << endl;
    cout << "\t5.    Generate report" << endl << endl;
	cout << "\t6.    Edit absences" << endl << endl;
    cout << "\t7.    Exit" << endl << endl;
	printStatus(currentStatus);
}

//printStatus to print currentStatus enumerated variable (status of list loaded/modified/etc.)
void Menu::printStatus(Status currentStatus) {
	//Note that the function uses ANSI escape sequences for colors, which change dependent on system.
	switch (currentStatus) {
		case NOT_LOADED: // Light Red (c/12)
		{
			cout << "\u001b[31;1mWARN - Course List and Master List Not Loaded!" << endl;
			break;
		}
		case COURSE_LOADED: // Light Green (a/10)
		{
			cout << "\u001b[32;1mCourse List Loaded Successfully." << endl;
			break;
		}
		case MASTER_LOADED: // Light Green (a/10)
		{
			cout << "\u001b[32;1mMaster List Loaded Successfully." << endl;
			break;
		}
		case MASTER_MOD: // Orange/Gold (6)
		{
			cout << "\u001b[33mWARN - Master List Modified, Unsaved Changes Present!" << endl;
			break;
		}
		case MASTER_SAVED: // Dark Green (2)
		{
			cout << "\u001b[32mMaster List Saved Successfully." << endl;
			break;
		}
		case ERROR: // Dark Red (4)
		{
			cout << "\u001b[31mERR - Error, unexpected status!" << endl;
			break;
		}
		default:
		{
			break;
		}

	}
	// Reset Color Code
	cout << "\u001b[0m";
}

//printSubMenu function to print submenu for generating reports.
void Menu::printSubMenu() {
    cout << endl << "1. Generate report for all students; showing only the most recent absence for each student." << endl;
    cout << "2. Generate report for students with absences that match or exceed..." << endl;
}

// Cross Platform Clearscreen Support
void Menu::clearScreen() {
    //Print 100 newlines:
    //cout << string(100, '\n');
    //Windows System Call:
    system("cls");
}

// Cross Platform Pause Support
void Menu::systemPause() {
    cin.ignore(1024, '\n');
    cout << "Press enter to continue..." << endl;
    cin.get();
    //Windows System Call:
    //system("pause");
}

//colorPicker function -- code more or less identical from printStatus(), except just the ANSI color codes.
void Menu::colorPicker(Status currentStatus) {
	switch (currentStatus) {
		case NOT_LOADED: // Light Red (c/12)
		{
			cout << "\u001b[31;1m" << endl;
			break;
		}
		case COURSE_LOADED: // Light Green (a/10)
		{
			cout << "\u001b[32;1m" << endl;
			break;
		}
		case MASTER_LOADED: // Light Green (a/10)
		{
			cout << "\u001b[32;1m" << endl;
			break;
		}
		case MASTER_MOD: // Orange/Gold (6)
		{
			cout << "\u001b[33m" << endl;
			break;
		}
		case MASTER_SAVED: // Dark Green (2)
		{
			cout << "\u001b[32m" << endl;
			break;
		}
		case ERROR: // Dark Red (4)
		{
			cout << "\u001b[31m" << endl;
			break;
		}
		default:
		{
			break;
		}
	}
}