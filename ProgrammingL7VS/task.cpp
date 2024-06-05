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
		cout << "Ѕыла подана команда на закрытие приложени€" << endl;
	}
	else {
		cout << "Ѕыл введен неподдерживаемый номер" << endl;
	}
}

void doAddForNumber() {
	int number = stoi(printMessageAndGetInput("\t¬ведите номер, по которому будет добавлен элемент(нумераци€ с единицы):\n\t", isInt));
	number--;

	cout << endl;

	if (number < 0 || number > getSizeOfStructure()) {
		cout << "Ѕыл введен некорректный номер" << endl;
		return;
	}

	cout << "\t¬ведите значени€ полей добавл€емого элемента\n" << endl;
	Employee employee = createEmployeeFromConsole();

	addForNumber(number, employee);

	cout << endl;
	cout << "Ёлемент был добавлен на " << (number + 1) << " позицию" << endl;
}

Employee createEmployeeFromConsole() {
	string name{};
	int age{};
	string familyPosition{};

	name = printMessageAndGetInput("\t¬ведите ‘»ќ:\n\t");
	age = stoi(printMessageAndGetInput("\t¬ведите возраст:\n\t", [](const string& s) {
			return isInt(s) && stoi(s) >= 0;
		}));
	familyPosition = printMessageAndGetInput("\t¬ведите семейное положение:\n\t");

	return Employee(name, age, familyPosition);
}

void doPrintAll() {
	printAll();
}

void doSetEmptyFields() {
	setEmptyFields();
}