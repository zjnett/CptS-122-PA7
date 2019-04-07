#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

enum Status {
	NOT_LOADED,
	COURSE_LOADED,
	MASTER_LOADED,
	MASTER_MOD,
	MASTER_SAVED,
	ERROR
};