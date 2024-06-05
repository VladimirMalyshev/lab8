#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "constants.h"
#include "functions.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <experimental/filesystem>

using namespace std;
using namespace constants;

bool isInt(const string& str) {
    if (str.empty())
        return false;
    for (int i = 0; i < str.length(); i++) {
        if (i == 0 && (str[i] == '-' || str[i] == '+') && str.length() != 1) {
            continue;
        }
        else if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isDouble(const string& str) {
    bool point{ false };
    if (str.empty())
        return false;
    for (int i = 0; i < str.length(); i++) {
        if (i == 0 && (str[i] == '-' || str[i] == '+') && str.length() != 1) {
            continue;
        }
        else if (
            (str[i] == ',') &&
            !point &&
            (
                str.length() != 1 &&
                !(str.length() == 2 &&
                    (str[i] == '+' || str[i] == '-')
                    )
                )
            ) {
            point = true;
        }
        else if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;

}

void repeatInputUntilCorrect(string& str, bool (condition)(const string&)) {
    while (!condition(str)) {
        wcout << L"Был произведен некорректный ввод, попробуйте снова: " << endl;
        getline(cin, str);
    }
}

string printMessageAndGetInput(const string& message, bool (*condition)(const string&)) {
    cout << message;
    string input;
    getline(cin, input);

    repeatInputUntilCorrect(input, condition);

    return input;
}

string printMessageAndGetInput(const string& message) {
    return printMessageAndGetInput(message,
        [](const string& str) { return !str.empty(); }
    );
}

string getAllFromFileOrEmptyString(const string& ifile) {
    ifstream fi(ifile);

    if (!fi.is_open()) {
        cout << "Файл не открылся, возможно был указан неправильный путь до файла(" << experimental::filesystem::absolute(ifile) << ")" << endl;
        exit(-1);
    }

    string str{};
    string temp{};

    while (!fi.eof() && getline(fi, temp)) {
        str.append(temp);
        str.append("\n");
    }

    if (!str.empty())
        str.resize(str.length() - 1);

    return str;
}

int getMode() {
    string message = "Список доступных команд:\n";

    message.append(to_string(ADD_FOR_NUMBER));
    message.append(") Добавить элемент.\n");
    message.append(to_string(PRINT_ALL));
    message.append(") Печать всех элементов.\n");
    message.append(to_string(SET_EMPTY_FIELDS));
    message.append(") Сброс значений полей всех элементов.\n");
    message.append(to_string(EXIT));
    message.append(") Выход\n");


    string str = printMessageAndGetInput(message,
        [](const string& str) { return isInt(str); }
    );

    int res = stoi(str);

    return res;
}

void saveIntoFile(const string& str, const string& ofile) {
    fstream out(ofile, ios::out);
    if (out.is_open()) {
        out << str;
        out.close();
        cout << "Сохранено в файл " << experimental::filesystem::absolute(ofile) << endl;
    }
    else cout << "Путь указан неправильно, данные не были сохранены в файл(" << experimental::filesystem::absolute(ofile) << ")" << endl;

}

string getFileNameOrDefault(const string& message, const string& defaultFileName) {
    cout << message << endl;
    string file{};
    getline(cin, file);

    if (file.empty()) return defaultFileName;

    return file;
}

map<string, string> loadConfiguration() {
    ifstream fi(CONFIGURATION_PATH);

    if (!fi.is_open()) {
        cout << "Файл с конфигурацией не был найден(" << experimental::filesystem::absolute(CONFIGURATION_PATH) << ")" << endl;
        return map<string, string>();
    }

    map<string, string> result = map<string, string>();
    string temp{};
    int t = -1;

    while (getline(fi, temp)) {
        t = -1;
        for (int i = 0; i < temp.length(); i++) {
            if (temp[i] == '=') {
                t = i;
                break;
            }
        }

        if (t == -1) continue;

        result.insert(pair<string, string>(temp.substr(0, t), temp.substr(static_cast<size_t>(t) + 1, temp.length() - t - 1)));
    }

    return result;

}