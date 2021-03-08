#include "Calculation.h"

using namespace std;

Calculation::Calculation(VariateManager& vm)
{
    Expression = "";
    Ans = 0;
    VM = &vm;
}
Calculation::Calculation(VariateManager& vm, string Exp)
{
    Expression = Exp;
    Ans = 0;
    VM = &vm;
    getAns();
}
void Calculation::changeExprssion(string Exp)
{
    Expression = Exp;
    Ans = 0;
    getAns();
}
double Calculation::ans()
{
    return Ans;
}
void Calculation::DiviceZero()
{
    ErrorManager err(2);
    err.throwError();
}
void Calculation::Undefine()
{
    ErrorManager err(1);
    err.throwError();
}
void Calculation::TypeError()
{
    ErrorManager err(3);
    err.throwError();
}

void Calculation::getAns() //计算表达式的值
{
    pos = 0;
    OPTS.clear(); //操作数
    OPTR.clear(); //运算符
    char tmp;

    trim();
    if (Expression.size() == 2)
    {
        Ans = 0;
        return;
    }

    tmp = Expression[pos];
    OPTR.push(tmp);
    pos++;
    for (; pos < Expression.size(); pos++)
    {
        tmp = Expression[pos];
        if (pos != 0)
        {
            if (In(Expression[pos - 1]) && tmp == '-' && Expression[pos - 1] != ')') //支持相反数
            {
                double num = getNum();
                pos--;
                OPTS.push(num);
                continue;
            }
        }
        if (!In(tmp))
        {
            double num = getNum();
            pos--;
            OPTS.push(num);
        }
        else
        {
            if (OPTR.isEmpty())
            {
                OPTR.push(tmp);
            }
            else
            {
                char opr;
                OPTR.pop(opr);
                int cmp = Precede(opr, tmp);
                if (cmp == 1)
                {
                    if (tmp != ')')
                    {
                        bool flag;
                        while (Precede(opr, tmp) == 1)
                        {
                            double x1, x2;
                            OPTS.pop(x1);
                            OPTS.pop(x2);
                            double ans = Operate(x2, opr, x1);
                            OPTS.push(ans);
                            flag = OPTR.pop(opr);
                            if (!flag)
                                break;
                        }
                        if (flag)
                            OPTR.push(opr);
                        OPTR.push(tmp);
                    }
                    else
                    {
                        while (opr != '(')
                        {
                            double x1, x2;
                            OPTS.pop(x1);
                            OPTS.pop(x2);
                            double ans = Operate(x2, opr, x1);
                            OPTS.push(ans);
                            OPTR.pop(opr);
                        }
                    }
                }
                else if (cmp == -1) //如果栈顶符号小于当前运算符，那么继续往后判断
                {
                    OPTR.push(opr);
                    OPTR.push(tmp);
                }
                else if (cmp == 0)
                {
                    //什么也不做，括号结束
                }
            }
        }
    }

    OPTS.pop(Ans);
    return;
}

void Calculation::trim()
{
    string tmp = "#";
    for (int i = 0; i < Expression.size(); i++)
    {
        if (Expression.substr(i,1) != " ")
        {
            tmp.append(Expression.substr(i, 1));
        }
    }
    tmp.append("#");
    Expression = tmp;
}

double Calculation::getNum() //获取变量或则是数字
{
    double f = 1;
    double d = 0;
    double b = 0.1;
    bool getNum = false;
    char tmp = Expression[pos];
    if (tmp == '-')
    {
        pos++;
        f = -1;
        tmp = Expression[pos];
    }
    while (isNum(tmp))
    {
        getNum = true;
        d *= 10;
        d += tmp - '0';
        pos++;
        tmp = Expression[pos];
    }
    if (tmp == '.')
    {
        getNum = true;
        pos++;
        tmp = Expression[pos];
        while (isNum(tmp))
        {
            d += (tmp - '0') * b;
            b /= 10;
            pos++;
            tmp = Expression[pos];
        }
    }
    if(getNum)
        return d * f; //如果获取到了数字那就返回去
    else //如果没有获取数字，那么就是一个变量。
    {
        string name;
        while (!In(tmp))
        {
            name.append(Expression.substr(pos, 1));
            pos++;
            tmp = Expression[pos];
        }
        int type = VM->getType(name);
        switch (type)
        {
        case -1:
            Undefine();
            return 0;
        case 1:
            return (double)VM->getInt(name);
        case 2:
            return VM->getDouble(name);
        case 3:
            return (double)VM->getChar(name);
        case 4:
            TypeError();
            return 0;
        }
    }
}
bool Calculation::isNum(char ch)
{
    return ch <= '9' && ch >= '0';
}
bool Calculation::isBrackets(char ch) 
{
    return ch == '(';
}

int Calculation::In(char optr) //判断是否是操作符
{
    switch (optr)
    {
    case '+':
        return 1;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 4;
    case '(':
        return 5;
    case ')':
        return 6;
    case '#':
        return 7;
    case '^':
        return 8;
    }
    return 0;
}
int Calculation::Precede(char t1, char t2) //比较两个符号的优先级顺序
{
    if (t1 == '#')
    {
        if (t2 == '#' || t2 == ')')
        {
            return 2;
        }
        else
        {
            return -1;
        }
    }
    if (t1 == ')')
    {
        if (t2 == '(')
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    if (t1 == '(')
    {
        if (t2 == ')')
        {
            return 0;
        }
        else if (t2 == '#')
        {
            return 2;
        }
        else
        {
            return -1;
        }
    }
    if (t2 == '(')
    {
        return -1;
    }
    if (t2 == ')' || t2 == '#')
    {
        return 1;
    }

    if (Order(t1) < Order(t2))
    {
        return -1;
    }

    return 1;
}
int Calculation::Order(char optr) //运算优先级
{
    if (optr == '+' || optr == '-')
    {
        return 1;
    }
    if (optr == '*' || optr == '/')
    {
        return 2;
    }
    if (optr == '^')
    {
        return 3;
    }
}
double Calculation::Operate(double a, char optr, double b) //运算两个操作符
{
    switch (optr)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
            DiviceZero();
        else
            return a / b;
    case '(':
        break;
    case ')':
        break;
    case '#':
        break;
    case '^':
        return pow(a, b);
    }
    return -1;
}