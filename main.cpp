#include <iostream>
#include <string>
#include <sstream>

#include "table.h"

using  namespace std;

int main(int argc, char *argv[]) {
    ifstream myFile;
    if (argc > 1 ) {
        myFile.open(argv[1]);
    } else {
        myFile.open("testCSV/test9.csv");
    }
    Table tbl(myFile);

    cout << tbl << endl;

    myFile.close();
}

