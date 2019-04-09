/*
Programmer: Zach Nett
Class: CptS 122; Lab Section 5
Programming Assignment: PA7
File: Menu.h
Description: This program tracks attendance for a class, which can be viewed, modified, and have reports made based on.
*/

#include "PA7.h"

class Menu {
public:

	//printMenu function to print menu art and options.
	//As usual, ASCII art generated on patorjk.
	void printMenu(Status currentStatus);

	//printSubMenu function to print submenu for generating reports.
	void printSubMenu();

	//printStatus to print currentStatus enumerated variable (status of list loaded/modified/etc.)
	void printStatus(Status currentStatus);

	// Cross Platform Clearscreen Support Function
	void clearScreen();

	// Cross Platform Pause Support Function
	void systemPause();

	//colorPicker function -- code more or less identical from printStatus(), except just the ANSI color codes.
	void colorPicker(Status currentStatus);
};