#include "CodeInterpreter.h"

CodeInterpreter::CodeInterpreter()
{
	srand((unsigned)time(NULL));
	fileName = "";
	code = "";
}
CodeInterpreter::CodeInterpreter(string File)
{
	srand((unsigned)time(NULL));
	fileName = File;
	ReadFile();
}
void CodeInterpreter::FileError()
{
	ErrorManager err(6);
	err.throwError();
}
void CodeInterpreter::RandError()
{
	ErrorManager err(7);
	err.throwError();
}
void CodeInterpreter::CodeError()
{
	ErrorManager err(8);
	err.throwError();
}

void CodeInterpreter::ReadFile()
{
	if (fileName.empty())
		return;
	ifstream infile;
	infile.open(fileName);   //将文件流对象与文件连接起来 
	if (!infile)
	{
		FileError();	//文件打开失败
	}

	code = "";
	string s;
	while (getline(infile, s))
	{
		code.append(s);
		s = "\n";
		code.append(s);
	}
	infile.close();             //关闭文件输入流 

	//cout << code;
}
int CodeInterpreter::getRandInt(int min, int max, bool containMin, bool containMax)
{
	if (min > max)
	{
		RandError();
	}
	if (max == min && (!containMin || !containMax))
	{
		RandError();
	}
	if (max - min == 1 && !(containMax || containMin))
	{
		RandError();
	}
	
	if (containMin && containMax)
	{
		return rand() % (max - min + 1) + min;
	} 
	else if (containMin && !containMax)
	{
		return rand() % (max - min) + min;
	}
	else if (!containMin && containMax)
	{
		return rand() % (max - min) + min + 1;
	}
	else
	{
		return rand() % (max - min - 1) + min + 1;
	}
}
double CodeInterpreter::getRandDouble(double min, double max, bool containMin, bool containMax)
{
	if (min > max)
	{
		RandError();
	}
	if (max == min && (!containMin || !containMax))
	{
		RandError();
	}
	if (max - min <= 1e-6 && !(containMax && containMin))
	{
		RandError();
	}
	if (min == max) return min;

	double tmp = min + max * (double)rand() / (double)(RAND_MAX + 1);
	if (tmp == min && !containMin)
	{
		tmp += 1e-6;
	}
	if (tmp == max && !containMax)
	{
		tmp -= 1e-6;
	}
	return tmp;
}
void CodeInterpreter::SetSeed(unsigned int Seed)
{
	srand(Seed);
}
bool CodeInterpreter::HaveMeaning(char ch)
{
	return ch >= 33;
}
bool CodeInterpreter::SentenceBegin(char ch)
{
	return (ch=='\\') || (ch == '[') || (ch == '\"') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
bool CodeInterpreter::NameValid(char ch) //变量名
{
	if (ch >= '0' && ch <= '9')
		return true;
	if (ch >= 'a' && ch <= 'z')
		return true;
	if (ch >= 'A' && ch <= 'Z')
		return true;
	if (ch == '_')
		return true;
	return false;
}
bool CodeInterpreter::NameBeginValid(char ch) //变量名开头
{
	if (ch >= 'a' && ch <= 'z')
		return true;
	if (ch >= 'A' && ch <= 'Z')
		return true;
	if (ch == '_')
		return true;
	return false;
}
bool CodeInterpreter::isAlpha(char ch)
{
	if (ch >= 'a' && ch <= 'z')
		return true;
	if (ch >= 'A' && ch <= 'Z')
		return true;
	return false;
}
bool CodeInterpreter::isNum(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}
string CodeInterpreter::Trim(string cs) //删掉所有空白字符和控制字符
{
	string ans;
	int stringLayer = 0;
	for (int i = 0; i < cs.size(); i++)
	{
		if (cs[i] == '\"')
		{
			if (i == 0 || (i > 0 && cs[i - 1] != '\\'))
			{
				stringLayer = !stringLayer;
			}
		}
		if (HaveMeaning(cs[i]))
		{
			ans.append(cs.substr(i, 1));
		}
		else if (stringLayer != 0)
		{
			ans.append(cs.substr(i, 1));
		}
	}
	return ans;
}
string CodeInterpreter::ToString(double d, int decimal)
{
	decimal = decimal < 0 ? 0 : decimal;
	char dd[20];
	switch (decimal) {
	case 0:
		sprintf_s(dd, "%.0lf", d);
		break;
	case 1:
		sprintf_s(dd, "%.1lf", d);
		break;
	case 2:
		sprintf_s(dd, "%.2lf", d);
		break;
	case 3:
		sprintf_s(dd, "%.3lf", d);
		break;
	case 4:
		sprintf_s(dd, "%.4lf", d);
		break;
	case 5:
		sprintf_s(dd, "%.5lf", d);
		break;
	default:
		sprintf_s(dd, "%.6lf", d);
		break;
	}
	string tmp = dd;
	return tmp;
}

void CodeInterpreter::LineInterpreter(string cs)
{
	int index = 0;
	int layer = 0;
	int sq_layer = 0;
	int brackets_layer = 0;
	for (int i = 0, j, k; i < cs.size(); i++)
	{
		if (cs[i] == '{') layer++;
		else if (cs[i] == '}')layer--;
		else if (layer == 0 && cs[i] == ';')
		{
			SingleCode(cs.substr(index, i - index));
			index = i + 1;
		}
		else if (cs[i] == '[') sq_layer++;
		else if (cs[i] == ']') sq_layer--;
		else if (cs[i] == '(') brackets_layer++;
		else if (cs[i] == ')') brackets_layer--;
		if (layer < 0 || sq_layer < 0 || brackets_layer < 0) CodeError();
	}
}
void CodeInterpreter::SingleCode(string cs) //解释单个语句（递归解释）
{
	int Times = 1;
	int splitSpace = -1;
	Calculation Cal(VM); //计算器
	for (int i = cs.size() - 1; i >= 1; i--)
	{
		if (cs[i] == 'X' && cs[i-1] == '}')
		{
			splitSpace = i;
			Cal.changeExprssion(cs.substr(i + 1, cs.size() - i - 1));
			Times = (int)Cal.ans();
			break;
		}
		else if (cs[i] == ']' || cs[i] == '\"') break;
	}
	Times = Times > 0 ? Times : 0;

	if (Times == 0)
		return;
	else
	{
		if (splitSpace == -1) //没有多次重复
		{
			Data ans = getExpression(cs, Cal);
			if (ans.type == 1)
				Output(ans.d);
			else if (ans.type == 2)
				Output(ans.s);
		}
		else
		{
			if (cs[0] == '{') //对于多个表达式
			{
				if (cs[splitSpace - 1] != '}')
					CodeError();
				while (Times--)
				{
					int index = 1;
					int layer = 0; //确保里面没有大括号的重复
					for (int i = 1; i < splitSpace - 1; i++)
					{
						if (cs[i] == '{')layer++;
						else if (cs[i] == '}')layer--;
						else if (layer == 0 && cs[i] == ';')
						{
							SingleCode(cs.substr(index, i - index));
							index = i + 1;
						}
						if (layer < 0)CodeError();
					}
				}
			}
			else
			{
				while (Times--) //多次单个式子
				{
					Data ans = getExpression(cs.substr(0, splitSpace), Cal);
					if (ans.type == 1)
						Output(ans.d);
					else if (ans.type == 2)
						Output(ans.s);
				}
			}
		}
	}
}
Data CodeInterpreter::getExpression(string cs, Calculation &Cal)
{
	Data ans;
	if (cs.size() == 0)
	{
		ans.type = 1;
		ans.d = 0;
		return ans;
	}
	else if (cs.size() == 1 && cs[0] == '\\')
	{
		ans.s = "\n";
		ans.type = 2;
		return ans;
	}

	if (cs[0] == '[')
	{
		if (cs[cs.size() - 1] == ']')
		{
			map<int, int> m;
			m[0] = 0;
			int layer = 0;
			int num = 1;
			for (int i = 1; i < cs.size() - 1; i++)
			{
				if (cs[i] == '[')layer++;
				else if (cs[i] == ']')layer--;
				else if (layer == 0 && cs[i] == ',')
				{
					m[num++] = i;
				}
			}
			m[num] = cs.size() - 1;
			if (num == 1)
			{
				return getExpression(cs.substr(1, cs.size() - 2), Cal);
			}
			else
			{
				int choose = getRandInt(0, num, true, false);
				return getExpression(cs.substr(m[choose] + 1, m[choose + 1] - m[choose] - 1), Cal);
			}
		}
	}
	else if (isAlpha(cs[0]) && cs[1] == '[')
	{
		if (cs[cs.size() - 1] == ']')
		{
			int split = -1;
			int layer = 0;
			for (int i = 2; i < cs.size() - 1; i++)
			{
				if (cs[i] == '[')layer++;
				else if (cs[i] == ']')layer--;
				else if (layer == 0 && cs[i] == ',')
				{
					split = i;
					break;
				}
			}
			if (split == -1) CodeError();
			Data min = getExpression(cs.substr(2, split - 2), Cal);
			Data max = getExpression(cs.substr(split + 1, cs.size() - split - 2), Cal);
			if (min.type != 1 || max.type != 1) CodeError();
			if (cs[0] == 'i')
			{
				int minInt = (int)min.d;
				int maxInt = (int)max.d;
				ans.d = getRandInt(minInt, maxInt, true, false);
				ans.type = 1;
				return ans;
			}
			else if (cs[0] == 'f')
			{
				ans.d = getRandDouble(min.d, max.d, true, false);
				ans.type = 1;
				return ans;
			}
			else if (cs[0] == 'c')
			{
				int minInt = (int)min.d;
				int maxInt = (int)max.d;
				char tmp = getRandInt(minInt, maxInt, true, false);
				ans.s = tmp;
				ans.type = 2;
				return ans;
			}
			else
			{
				CodeError();
			}
		}
	}
	else if (cs[0] == '\"')
	{
		if (cs[cs.size() - 1] != '\"') CodeError();
		ans.s = cs.substr(1, cs.size() - 2);
		ans.type = 2;
		return ans;
	}
	else if (cs[0] == '\'')
	{
		if (cs.size() != 3 || cs[2] != '\'') CodeError();
		char tmp = cs[1];
		ans.d = tmp;
		ans.type = 1;
		return ans;
	}

	if (cs.substr(0, 5) == "seed(")
	{
		if (cs[cs.size() - 1] != ')')CodeError();
		Data tmp = getExpression(cs.substr(5, cs.size() - 6), Cal);
		if (tmp.type != 1)CodeError();
		SetSeed((unsigned int)tmp.d);
		ans.type = 0;
		return ans;
	}

	int isVal = -1; //是变量
	for (int i = 0; i < cs.size(); i++)
	{
		if (cs[i] == '=')
		{
			isVal = i;
			break;
		}
	}
	if (isVal != -1) //声明变量
	{
		Data tmp = getExpression(cs.substr(isVal + 1, cs.size() - isVal - 1), Cal);
		if (tmp.type == 1) VM.insert(cs.substr(0, isVal), tmp.d);
		else if (tmp.type == 2) VM.insert(cs.substr(0, isVal), tmp.s);
		ans.type = 0;
		return ans;
	}

	string expression; //如果上述情况都不是，那么就是一个复杂的多项式计算。
	int index = 0;
	int layer = 0;
	for (int i = 0; i < cs.size(); i++)
	{
		if (cs[i] == '[')
		{
			if (layer == 0)
				index = i;
			layer++;
		}
		else if (cs[i] == ']')
		{
			if (layer == 1)
			{
				if (index != 0 && isAlpha(cs[index - 1]))
				{
					expression.pop_back();
					Data tmp = getExpression(cs.substr(index - 1, i - index + 2), Cal);
					if (tmp.type != 1) CodeError();
					expression.append(ToString(tmp.d, 6));
				}
				else
				{
					Data tmp = getExpression(cs.substr(index, i - index + 1), Cal);
					if (tmp.type != 1) CodeError();
					expression.append(ToString(tmp.d, 6));
				}
			}
			layer--;
		}
		else if (layer == 0)
		{
			expression.append(cs.substr(i, 1));
		}
		if (layer < 0) CodeError();
	}
	Cal.changeExprssion(expression);
	ans.d = Cal.ans();
	ans.type = 1;
	return ans;
}
void CodeInterpreter::autoOut(int type)
{
	switch (type)
	{
	case 0:
		break;
	case 1:
		int tmp;
		s_int.pop(tmp);
		Output(tmp);
		break;
	case 2:
		double tmp2;
		s_double.pop(tmp2);
		Output(tmp2);
		break;
	case 3:
		char tmp3;
		s_char.pop(tmp3);
		Output(tmp3);
		break;
	case 4:
		string tmp4;
		s_string.pop(tmp4);
		Output(tmp4);
		break;
	}
}
void CodeInterpreter::Output()
{
	cout << endl;
}
void CodeInterpreter::Output(string data)
{
	cout << data;
}
void CodeInterpreter::Output(double data)
{
	cout << data;
}
void CodeInterpreter::Output(int data)
{
	cout << data;
}
void CodeInterpreter::Output(char data)
{
	cout << data;
}


void CodeInterpreter::interpreter()	//解释器
{
	writeFile.erase();
	checkFile.erase();
	transmitInfor.erase();
	code.append(";");
	LineInterpreter(Trim(code));
}


void CodeInterpreter::changeCode(string Code, bool reset)
{
	if (reset)
	{
		VM.reset();
		srand((unsigned)time(NULL));
	}
	code = Code;
	fileName = "";
}
void CodeInterpreter::changeFileName(string FileName, bool reset)
{
	if (reset)
	{
		VM.reset();
		srand((unsigned)time(NULL));
	}
	fileName = FileName;
	ReadFile();
}
void CodeInterpreter::reset()
{
	srand((unsigned)time(NULL));
	fileName = "";
	code = "";
	VM.reset();
}