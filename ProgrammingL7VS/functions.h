#pragma once

#include <iostream>
#include <string>
#include <map>

using namespace std;

bool isInt(const string& str);
bool isDouble(string& str);
string getAllFromFileOrEmptyString(const string& ifile);
int getMode();
void saveIntoFile(const string& str, const string& ofile);
string printMessageAndGetInput(const string& message, bool (*condition)(const string&));
string printMessageAndGetInput(const string& message);
string getFileNameOrDefault(const string& message, const string& defaultFileName);
map<string, string> loadConfiguration();