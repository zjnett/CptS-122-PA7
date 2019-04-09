/*
Programmer: Zach Nett
Class: CptS 122; Lab Section 5
Programming Assignment: PA7
File: PA7.h
Description: This program tracks attendance for a class, which can be viewed, modified, and have reports made based on.
*/

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>

// Enum type to track current program status.
enum Status {
	NOT_LOADED,
	COURSE_LOADED,
	MASTER_LOADED,
	MASTER_MOD,
	MASTER_SAVED,
	ERROR
};