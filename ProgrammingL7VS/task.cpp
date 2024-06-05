#include <iostream>
#include <string>

#include "constants.h"
#include "structure.h"
#include "functions.h"
#include "task.h"


using namespace std;
using namespace constants;

void doTask() {
	int mode{EXIT};

	loadStructure();

	cout << endl;

	do {
		mode = getMode();

		doChooshedFunction(mode);

		cout << endl << endl << endl;
	} while (mode != EXIT);

	saveStructureIntoFile();
}

void doChooshedFunction(const int mode) {
	cout << endl;
	if (mode == ADD_FOR_NUMBER) {
		doAddForNumber();
	}
	else if (mode == SET_EMPTY_FIELDS) {
		doSetEmptyFields();
	}
	else if (mode == PRINT_ALL) {
		doPrintAll();
	}
	else if (mode == EXIT) {
		cout << "���� ������ ������� �� �������� ����������" << endl;
	}
	else {
		cout << "��� ������ ���������������� �����" << endl;
	}
}

void doAddForNumber() {
	int number = stoi(printMessageAndGetInput("\t������� �����, �� �������� ����� �������� �������(��������� � �������):\n\t", isInt));
	number--;

	cout << endl;

	if (number < 0 || number > getSizeOfStructure()) {
		cout << "��� ������ ������������ �����" << endl;
		return;
	}

	cout << "\t������� �������� ����� ������������ ��������\n" << endl;
	Employee employee = createEmployeeFromConsole();

	addForNumber(number, employee);

	cout << endl;
	cout << "������� ��� �������� �� " << (number + 1) << " �������" << endl;
}

Employee createEmployeeFromConsole() {
	string name{};
	int age{};
	string familyPosition{};

	name = printMessageAndGetInput("\t������� ���:\n\t");
	age = stoi(printMessageAndGetInput("\t������� �������:\n\t", [](const string& s) {
			return isInt(s) && stoi(s) >= 0;
		}));
	familyPosition = printMessageAndGetInput("\t������� �������� ���������:\n\t");

	return Employee(name, age, familyPosition);
}

void doPrintAll() {
	printAll();
}

void doSetEmptyFields() {
	setEmptyFields();
}