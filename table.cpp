#include "table.h"

/** Acquires a cell, which is requested by provided address
 *
 * @param address of a requested cell in a csv table
 * @return a pointer to a cell
 */
string*  Table ::getCellAddress(const string& address) {
    istringstream iss(address);
    string col_name, pos;
    col_name = address.substr(0,address.find_first_of("0123456789"));
    pos = address.substr(address.find_first_of("0123456789"), string::npos);

    auto it = find(table.at("r_h").begin(), table.at("r_h").end(), pos);
    int index = it - table.at("r_h").begin();

    return &table.at(col_name)[index];
}

/** Calculates the cell's mathematical expression and updates the cell with the result
 *
 * @param cell a pointer to a cell
 * @param traceBack keeping a track of cells participating in calc, in order to avoid inf loop
 */
void Table ::calculateAndUpdate(string* cell, set<string> traceBack) {
    string all_op = "+-*/";
    if (cell->at(0) == '='){
        string expression = cell->substr(1, string::npos);
        size_t i = expression.find_first_of(all_op);
        char op = expression.at(i);
        istringstream iss(expression);

        string arg1, arg2;
        getline(iss, arg1, op);
        getline(iss, arg2, op);

        if (traceBack.find(arg1) != traceBack.end() or traceBack.find(arg2) != traceBack.end()){
            throw invalid_argument("There is an eternal loop in csv data");
        }

        string* cellR = getCellAddress(arg1);
        if (cellR->find_first_of(all_op) != string::npos){
            traceBack.insert(arg1);
            calculateAndUpdate(cellR, traceBack);
        }
        string* cellL = getCellAddress(arg2);
        if (cellL->find_first_of(all_op) != string::npos){
            traceBack.insert(arg2);
            calculateAndUpdate(cellL, traceBack);
        }

        int val1 = stoi(*cellR);
        int val2 = stoi(*cellL);


        switch (op) {
            case '+':
                *cell = to_string(val1 + val2);
                break;
            case '-':
                *cell = to_string(val1 - val2);
                break;
            case '*':
                *cell = to_string(val1 * val2);
                break;
            case '/':
                *cell = to_string(val1 / val2);
                break;
        }
    }
}
