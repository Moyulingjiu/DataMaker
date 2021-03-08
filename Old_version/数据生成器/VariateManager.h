#pragma once

#include <map>
#include <string>
#include <iostream>
#include "ErrorManager.h"

using namespace std;

class VariateManager
{
	map<string, int> type;
	map<string, int> m_int;
	map<string, double> m_double;
	map<string, char> m_char;
	map<string, string> m_string;

	void checkName(string name);
	void NameInvalid();
	void Undefine();
public:
	VariateManager();
	VariateManager(VariateManager& other);
	bool insert(string name, int value);
	bool insert(string name, double value);
	bool insert(string name, char value);
	bool insert(string name, string value);
	int getType(string name);
	int getInt(string name);
	double getDouble(string name);
	char getChar(string name);
	string getString(string name);
	void reset();
};

