#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <vector>

#include "constants.h"
#include "functions.h"
#include "structure.h"

using namespace std;
using namespace constants;


multimap<int, Employee> structure;

map<string, string> configuration;

void loadStructure() {
	configuration = loadConfiguration();

	if (configuration.count(STRUCTURE_KEY) == 0) {
		cout << "Ключ " << STRUCTURE_KEY << " отсутствует в конфигурационном файле " << CONFIGURATION_PATH << endl;
		exit(-1);
	}

	string structurePath = configuration.at(STRUCTURE_KEY);

	string raw = getAllFromFileOrEmptyString(structurePath);

	if (raw.empty()) {
		return;
	}

	string temp{};

	Employee employee;

	int order = 0;
	int count = 0;

	int begin = 0, end = -1;

	for (int i = 0; i <= raw.length(); i++) {
		if (i == raw.length() || raw[i] == '\n') {
			end = i - 1;

			if (begin > end) continue;

			temp = raw.substr(begin, end - begin + 1);

			if (order == 0) {
				if (temp.empty()) {
					cout << "Некорректный формат в файле" << endl;
					exit(-1);
				}

				employee = Employee();
				employee.name = temp;
			}
			else if (order == 1) {
				if (!(isInt(temp) && stoi(temp) >= 0)) {
					cout << "Некорректный формат в файле" << endl;
					exit(-1);
				}

				employee.age = stoi(temp);
			}
			else {
				if (temp.empty()) {
					cout << "Некорректный формат в файле" << endl;
					exit(-1);
				}

				employee.familyPosition = temp;

				structure.insert(pair<int, Employee>{count, employee});
				count++;
			}
			order = (order + 1) % 3;
			begin = i + 1;
		}
	}

	if (order != 0) {
		cout << "Некорректный формат в файле" << endl;
		exit(100);
	}

	cout << "Было загружено " << count << " элементов в СПД" << endl;
}

void addForNumber(const int number, const Employee& employee) {
	vector<Employee> v(0);

	int sizeOfStructure = structure.size();

	for (int i = number; i < sizeOfStructure; i++) {
		pair<int, Employee> e = *structure.find(i);
		v.push_back(e.second);
		structure.erase(i);
	}

	structure.insert(pair<int, Employee>{number, employee});

	for (int i = 0; i < v.size(); i++) {
		structure.insert(pair<int, Employee>{number + 1 + i, v.at(i)});
	}
}

void printAll() {
	if (structure.empty()) {
		std::cout << "The list is empty.\n";
		return;
	}

	// Заголовок таблицы  
	cout << left << setw(5) << "No"
		<< setw(35) << "ФИО"
		<< setw(35) << "Возраст"
		<< setw(35) << "Семейное положение" << endl;
	cout << string(115, '-') << endl;

	// Вывод элементов списка  
	for (const auto& elem : structure) {
		cout << left << std::setw(5) << elem.first + 1
			<< setw(35) << elem.second.name
			<< setw(35) << elem.second.age
			<< setw(35) << elem.second.familyPosition << endl;
	}
}

void setEmptyFields() {
	if (structure.empty()) {
		cout << "Действие не было совершенно, нет элементов в СПД" << endl;
		return;
	}

	for (auto& elem : structure) {
		elem.second.name = "_null";
		elem.second.age = 0;
		elem.second.familyPosition = "_null";
	}

	cout << "Значения были сброшены" << endl;
}

void saveStructureIntoFile() {
	if (structure.empty()) {
		cout << "Элементов в СПД нет, сохранять нечего" << endl;
		return;
	}

	string structurePath = configuration.at(STRUCTURE_KEY);

	string strToSave{};

	for (const auto& elem : structure) {
		strToSave.append(employeeToString(elem.second));
		strToSave.append("\n");
	}

	strToSave.resize(strToSave.length() - 1);

	cout << "Сохранение СПД в файл..." << endl;
	saveIntoFile(strToSave, structurePath);
}

string employeeToString(const Employee& employee) {
	string result{};

	result.append(employee.name);
	result.append("\n");
	result.append(to_string(employee.age));
	result.append("\n");
	result.append(employee.familyPosition);

	return result;
}

int getSizeOfStructure() {
	return structure.size();
}

