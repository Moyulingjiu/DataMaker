#pragma once

#include <string>

using namespace std;

class ErrorManager
{
	int err;
	string infor;
public:
	ErrorManager();
	ErrorManager(int ErrorType);
	ErrorManager(int ErrorType, string infor);
	void throwError();
};

