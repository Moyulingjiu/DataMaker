#include "ErrorManager.h"

#include <iostream>

ErrorManager::ErrorManager()
{
	err = 0;
	infor = "Unexpected Error";
}
ErrorManager::ErrorManager(int ErrorType)
{
	err = ErrorType;
	switch (ErrorType)
	{
	case 1:
		infor = "Undefined"; //未定义的东西（变量名、函数名）
		break;
	case 2:
		infor = "Divisor is 0"; //除数为0
		break;
	case 3:
		infor = "Type error";	//格式错误（比如字符串变量拿去做加法）
		break;
	case 4:
		infor = "Variate's name invalid"; //变量名字不合法
		break;
	case 5:
		infor = "Invalid operator"; //不合法的操作符
		break;
	case 6:
		infor = "File Error"; //文件错误
		break;
	case 7:
		infor = "The minimum value is less than the maximum value"; //最小值小于最大值
		break;
	case 8:
		infor = "Invalid Code"; //不合法的语句
		break;

	default:
		break;
	}
}
ErrorManager::ErrorManager(int ErrorType, string Information)
{
	err = ErrorType;
	infor = Information;
}
void ErrorManager::throwError()
{
	std::cout << "Error " << err << ":";
	std::cout << infor << endl;
	exit(-1);
}