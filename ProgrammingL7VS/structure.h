#pragma once

#include <string>
#include "constants.h"

using namespace std;
using namespace constants;

void loadStructure();
void saveStructureIntoFile();
void printAll();
void setEmptyFields();
int getSizeOfStructure();
void addForNumber(const int number, const Employee& employee);
string employeeToString(const Employee& employee);