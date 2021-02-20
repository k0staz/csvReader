#include <iostream>
#include <string>
#include <sstream>

#include "table.h"

using  namespace std;

int main() {
    ifstream myFile;
    myFile.open("test2.csv");

    Table tbl(myFile);

    cout << tbl << endl;

    myFile.close();
}

