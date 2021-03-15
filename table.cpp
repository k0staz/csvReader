#include "table.h"

/**
* @brief Constructs table from csv file
* @param File with comma-separated values (csv)
*/
Table ::Table(ifstream &File) {
    if (File) {
        string line, value;
        vector<pair<string, size_t>>indToCalc;
        bool first = true;

        while (File.good()) {
            getline(File, line, '\n');
            istringstream iss(line);
            if (first) {
                bool first_col = true;
                while (getline(iss, value, ',')) {
                    if (first_col) {
                        table["r_h"] = vector<string>();
                        col_order.emplace_back("r_h");
                        first_col = false;
                    }else if ( value.empty() ) {
                        throw invalid_argument("Column name can't be empty"); //Test for empty name of a column
                    } else {
                        if(value.find_first_of("0123456789") != string::npos){ //Test for a name to consist only of letters
                            throw invalid_argument("The name of the column can't hold any digits in it");
                        }
                        table[value] = vector<string>();
                        col_order.push_back(value);
                    }
                }
                first = false;
            } else {
                for (auto& x : col_order) {
                    getline(iss, value, ',');
                    if (value[0] != '=' or value.empty()) { //Test that cells contain only positive integers
                        for (auto& ch : value ) {
                            if (!isdigit(ch)) {
                                throw invalid_argument("Cells can contain only positive integers and should not be empty");
                            }
                        }
                    }
                    table[x].push_back(value);
                    if (value[0] == '=') {
                        indToCalc.emplace_back(make_pair(x, table[x].size()-1));
                    }
                }
            }
        }
        for (auto& x : indToCalc) {
            string cell = table[x.first].at(x.second);
            calculateAndUpdate(table[x.first][x.second]);
        }
    }
    }

/** Acquires a cell, which is requested by provided address
*
* @param address of a requested cell in a csv table
* @return a pointer to a cell
*/
string&  Table ::getCellAddress(const string& address) {
    istringstream iss(address);
    string col_name, pos;
    col_name = address.substr(0,address.find_first_of("0123456789"));
    pos = address.substr(address.find_first_of("0123456789"), string::npos);

    auto it = find(table.at("r_h").begin(), table.at("r_h").end(), pos);
    int index = it - table.at("r_h").begin();

    try{ //Test for an unexisting address of a cell
        return table.at(col_name)[index];
    } catch (...) {
        throw out_of_range("The cell with the address: " + address + " has not been found");
    }
}

/** Calculates the cell's mathematical expression and updates the cell with the result
 *
 * @param cell a pointer to a cell
 * @param traceBack keeping a track of cells participating in calc, in order to avoid inf loop
 */
void Table ::calculateAndUpdate(string& cell, set<string> traceBack) {
    string all_op = "+-*/";
    if (cell.at(0) == '='){
        string expression = cell.substr(1, string::npos);
        size_t i = expression.find_first_of(all_op);
        char op = expression.at(i);
        istringstream iss(expression);

        string arg1, arg2;
        getline(iss, arg1, op);
        getline(iss, arg2, op);

        if (traceBack.find(arg1) != traceBack.end() or traceBack.find(arg2) != traceBack.end()){
            throw invalid_argument("There is an eternal loop in csv data");
        }

        string cellR = getCellAddress(arg1);
        if (cellR.find_first_of(all_op) != string::npos){
            traceBack.insert(arg1);
            calculateAndUpdate(cellR, traceBack);
        }
        string cellL = getCellAddress(arg2);
        if (cellL.find_first_of(all_op) != string::npos){
            traceBack.insert(arg2);
            calculateAndUpdate(cellL, traceBack);
        }

        int val1 = stoi(cellR);
        int val2 = stoi(cellL);


        switch (op) {
            case '+':
                cell = to_string(val1 + val2);
                break;
            case '-':
                if (val1 <= val2) {
                    cell = "0";
                } else {
                    cell = to_string(val1 - val2);
                }
                break;
            case '*':
                cell = to_string(val1 * val2);
                break;
            case '/':
                cell = to_string(val1 / val2);
                break;
            default:
                throw invalid_argument("Unknown operator");
        }
    }
}

ostream& operator<<(ostream& os, const Table& tb){
    for(auto& col : tb.col_order){
        os << col << ",";
    }
    os << endl;
    for(int i = 0; i < tb.table.at("r_h").size(); i++){
        for(auto& col : tb.col_order){
            os << tb.table.at(col)[i] << ",";
        }
        os << endl;
    }
    return os;
}