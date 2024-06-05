#pragma once

#include <string>

using namespace std;

namespace constants {
	const int ADD_FOR_NUMBER = 1;
	const int SET_EMPTY_FIELDS = 3;
	const int PRINT_ALL = 2;
	const int EXIT = 4;

	const int E_NAME = 1;
	const int E_POSITION = 2;
	const int E_ADRESS = 3;

	const int CHOOSED_ASC = 1;
	const int CHOOSED_DESC = 2;

	const string CONFIGURATION_PATH = "configuration.properties";
	const string STRUCTURE_KEY = "structure_path";

	struct Employee {
		string name{};
		int age{};
		string familyPosition{};

		Employee() {

		}

		Employee(string name, int age, string familyPosition) {
			this->name = name;
			this->age = age;
			this->familyPosition = familyPosition;
		}
	};

	struct Node
	{
		Employee value;

		Node* next{};
		Node* prev{};
	};
}