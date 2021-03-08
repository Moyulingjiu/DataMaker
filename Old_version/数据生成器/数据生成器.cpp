#include "Calculation.h"
#include "ErrorManager.h"
#include "VariateManager.h"
#include "CodeInterpreter.h"

#include <iostream>
#include <string>

using namespace std;

CodeInterpreter CI;

void errorMessage(string command)
{
    cout << "Unable to understand the \"" << command << "\"" << endl;
    cout << "Please type \"help\" for help" << endl;
}
void help()
{
    cout << "暂未支持字符串中出现中文，请尽量只用英文。否则可能出现乱码。" << endl;
    cout << "对于任何有参数的命令，可以使用\"命令 -?\"来查询" << endl;
    cout << "dm\t编译文件，并运行文件" << endl;
    cout << "code\t运行单条代码" << endl;
    cout << "reset\t重置解释器" << endl;
    cout << "exit\t退出" << endl;
}

void dm_help()
{
    cout << "dm 文件名\t编译文件，并运行文件" << endl;
    cout << "dm -m 文件名\t编译文件，并运行文件，但是不会重置解释器，这意味着你的变量可能在之前的文件里声明过" << endl;
}
void dm(string command, string type, string filename)
{
    if (type.empty())
    {
        if (filename.empty())
        {
            errorMessage(command);
            return;
        }
        CI.changeFileName(filename, true);
        CI.interpreter();
    }
    else if (type == "m") //多文件执行
    {
        if (filename.empty())
        {
            errorMessage(command);
            return;
        }
        CI.changeFileName(filename, false); //不刷新
        CI.interpreter();
    }
    else if (type == "?")
    {
        dm_help();
    }
    else
    {
        errorMessage(command);
    }
}
void exit_help()
{
    cout << "exit\t退出" << endl;
}
void code_help()
{
    cout << "code 代码\t执行代码，但是不会重置解释器。" << endl;
    cout << "code -r 代码\t执行代码，重置解释器。" << endl;
}
void code(string command, string type, string code)
{
    if (type.empty())
    {
        if (code.empty())
        {
            errorMessage(command);
            return;
        }
        CI.changeCode(code, false);
        CI.interpreter();
    }
    else if (type == "r")
    {
        if (code.empty())
        {
            errorMessage(command);
            return;
        }
        CI.changeCode(code, true); //刷新
        CI.interpreter();
    }
    else if (type == "?")
    {
        code_help();
    }
    else
    {
        errorMessage(command);
    }
}
void reset_help()
{
    cout << "reset\t重置解释器" << endl;
}


int main(int argc, char* argv[])
{
    string filename;
    string command = "void";
    string right = "Data Maker [版本 0.0.2]";
    string workPlace = argv[0];

    if (argc >= 2)
    {
        filename = argv[1];
        CI.changeFileName(filename);
        CI.interpreter();
        return 0;
    }

    cout << right << endl << "工作环境：" << workPlace << endl << endl;
    while (1)
    {
        if (!command.empty()) cout << endl;
        cout << ">>>";
        getline(cin, command);
        if (command.empty()) continue;
        string c;
        string type;
        int split = -1;
        for (int i = 0; i < command.size(); i++) //获取命令
        {
            if (command[i] == ' ')
            {
                split = i;
                break;
            }
            c.append(command.substr(i, 1));
        }
        if (split != -1 && command.size() > split + 1 && command[split + 1] == '-') //获取命令格式
        {
            for (int i = split + 2; i < command.size(); i++)
            {
                if (command[i] == ' ')
                {
                    split = i;
                    break;
                }
                type.append(command.substr(i, 1));
            }
        }

        if (c == "help")
        {
            help();
        }
        else if (c == "dm")
        {
            dm(command, type, command.substr(split + 1, command.size() - split - 1));
        }
        else if (c == "exit")
        {
            if (type.empty())
                break;
            else if (type == "?")
                exit_help();
            else
                errorMessage(command);
        }
        else if (c == "code")
        {
            code(command, type, command.substr(split + 1, command.size() - split - 1));
        }
        else if (c == "reset")
        {
            if (type.empty())
                CI.reset();
            else if (type == "?")
                reset_help();
            else
                errorMessage(command);
        }
        else
        {
            errorMessage(command);
        }
    }
    return 0;
}
