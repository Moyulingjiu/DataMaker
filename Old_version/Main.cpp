#include "Calculation\Calculation.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // string fileName;

    // if (argc == 0)
    // {
    //     cin >> fileName;
    // }
    // else
    // {
    //     fileName = argv[1];
    // }

    string ex;
    cin >> ex;
    Calculation a(ex);
    cout << a.ans();


    return 0;
}