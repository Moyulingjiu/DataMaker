#include "VariateManager.h"

VariateManager::VariateManager()
{
	
}
VariateManager::VariateManager(VariateManager& other)
{
	type = other.type;
	m_int = other.m_int;
	m_double = other.m_double;
	m_char = other.m_char;
	m_string = other.m_string;
}
void VariateManager::checkName(string name)
{
	const string Reserved[] = { "file","seed" };
	for (auto i : Reserved)
	{
		if (i == name)
		{
			NameInvalid();
		}
	}

	if (name.size() == 0)
	{
		NameInvalid();
	}
	if (name[0] >= '0' && name[0] <= '9')
	{
		NameInvalid();
	}
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] >= '0' && name[i] <= '9')
		{
			continue;
		}
		else if (name[i] >= 'a' && name[i] <= 'z')
		{
			continue;
		}
		else if (name[i] >= 'A' && name[i] <= 'Z')
		{
			continue;
		}
		else if (name[i] == '_')
		{
			continue;
		}
		else
		{
			NameInvalid();
		}
	}
}
void VariateManager::NameInvalid()
{
	ErrorManager err(4);
	err.throwError();
}
void VariateManager::Undefine()
{
	ErrorManager err(1);
	err.throwError();
}

bool VariateManager::insert(string name, int value)
{
	if (type.count(name) == 0)
	{
		checkName(name);
		type[name] = 1;
		m_int[name] = value;
		return true;
	}
	else
	{
		return false;
	}
}
bool VariateManager::insert(string name, double value)
{
	if (type.count(name) == 0)
	{
		checkName(name);
		type[name] = 2;
		m_double[name] = value;
		return true;
	}
	else
	{
		return false;
	}
}
bool VariateManager::insert(string name, char value)
{
	if (type.count(name) == 0)
	{
		checkName(name);
		type[name] = 3;
		m_char[name] = value;
		return true;
	}
	else
	{
		return false;
	}
}
bool VariateManager::insert(string name, string value)
{
	if (type.count(name) == 0)
	{
		checkName(name);
		type[name] = 4;
		m_string[name] = value;
		return true;
	}
	else
	{
		return false;
	}
}

int VariateManager::getType(string name)
{
	if (type.count(name) != 0)
	{
		return type[name];
	}
	else
	{
		return -1;
	}
}
int VariateManager::getInt(string name)
{
	if (m_int.count(name) != 0)
	{
		return m_int[name];
	}
	else
	{
		Undefine();
		return 0;
	}
}
double VariateManager::getDouble(string name)
{
	if (m_double.count(name) != 0)
	{
		return m_double[name];
	}
	else
	{
		Undefine();
		return (double)0;
	}
}
char VariateManager::getChar(string name)
{
	if (m_char.count(name) != 0)
	{
		return m_char[name];
	}
	else
	{
		Undefine();
		return 0;
	}
}
string VariateManager::getString(string name)
{
	if (m_string.count(name) != 0)
	{
		return m_string[name];
	}
	else
	{
		Undefine();
		string tmp;
		return tmp;
	}
}

void VariateManager::reset()
{
	type.clear();
	m_int.clear();
	m_double.clear();
	m_char.clear();
	m_string.clear();
}