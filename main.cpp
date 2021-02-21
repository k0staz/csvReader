#include <iostream>
#include <string>
#include <sstream>

#include "table.h"

using  namespace std;

int main(int argc, char *argv[]) {
    ifstream myFile;
    myFile.open(argv[1]);
//    myFile.open("test.csv");

    Table tbl(myFile);

    cout << tbl << endl;

    myFile.close();
}

