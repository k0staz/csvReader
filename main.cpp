#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>

#include "table.h"

using  namespace std;

int main(int argc, char *argv[]) {
    ifstream myFile;
    if (argc > 1 ) {
        filesystem::path p{argv[1]};
        myFile.open(p);
    } else {
        myFile.open("test.csv");
    }
    Table tbl(myFile);

    cout << tbl << endl;

    myFile.close();
}

