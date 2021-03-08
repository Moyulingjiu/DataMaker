#pragma once

#include <string>
#include <cmath>
#include "Stack.h"
#include "VariateManager.h"
#include "ErrorManager.h"

using namespace std;

class Calculation
{
private:
    double Ans;
    string Expression;
    Stack<double> OPTS;    //������
    Stack<char> OPTR;   //�����
    int pos;    //��ǰ����λ
    VariateManager *VM;  //����������

    void getAns();
    void trim();
    double getNum();
    bool isNum(char ch);
    bool isBrackets(char ch);
    int In(char optr);
    int Precede(char t1, char t2);
    int Order(char optr);
    double Operate(double a, char optr, double b);

    void DiviceZero();
    void Undefine();
    void TypeError();
public:
    Calculation(VariateManager& vm);
    Calculation(VariateManager& vm, string Exp);
    void changeExprssion(string Exp);
    double ans();
};
