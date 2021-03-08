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
		infor = "Undefined"; //δ����Ķ���������������������
		break;
	case 2:
		infor = "Divisor is 0"; //����Ϊ0
		break;
	case 3:
		infor = "Type error";	//��ʽ���󣨱����ַ���������ȥ���ӷ���
		break;
	case 4:
		infor = "Variate's name invalid"; //�������ֲ��Ϸ�
		break;
	case 5:
		infor = "Invalid operator"; //���Ϸ��Ĳ�����
		break;
	case 6:
		infor = "File Error"; //�ļ�����
		break;
	case 7:
		infor = "The minimum value is less than the maximum value"; //��СֵС�����ֵ
		break;
	case 8:
		infor = "Invalid Code"; //���Ϸ������
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