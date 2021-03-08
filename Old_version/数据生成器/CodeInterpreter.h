#pragma once

#include "Calculation.h"
#include "ErrorManager.h"
#include "VariateManager.h"
#include "Stack.h"

#include <cstdlib> 
#include <cstdio> 
#include <cstring> 
#include <string>
#include <ctime>
#include <fstream>
#include <map>

using namespace std;

struct Data
{
	string s;
	double d;
	int type;
	Data()
	{
		type = 0;
	}
};

class CodeInterpreter //代码解释器
{
	string fileName;
	string code;
	VariateManager VM;
	Stack<int> s_int;
	Stack<double> s_double;
	Stack<char> s_char;
	Stack<string> s_string;

	string writeFile;	//写入的文件地址
	string checkFile;	//检查的文件地址
	string transmitInfor; //传递给检查文件的数据

	void ReadFile();
	void FileError();
	void RandError();
	void CodeError();
	int getRandInt(int min, int max,bool containMin,bool containMax);
	double getRandDouble(double min, double max, bool containMin, bool containMax);
	bool HaveMeaning(char ch);
	bool SentenceBegin(char ch);
	bool NameValid(char ch);
	bool NameBeginValid(char ch);
	bool isAlpha(char ch);
	bool isNum(char ch);
	string Trim(string cs);
	string ToString(double d, int decimal);

	void SetSeed(unsigned int Seed);
	void LineInterpreter(string cs);
	void SingleCode(string cs);
	Data getExpression(string cs, Calculation& Cal);
	void autoOut(int type);
	void Output();
	void Output(string data);
	void Output(double data);
	void Output(int data);
	void Output(char data);
public:
	CodeInterpreter();
	CodeInterpreter(string File);
	void interpreter();
	void changeCode(string Code, bool reset = false);
	void changeFileName(string FileName, bool reset = false);
	void reset();
};

