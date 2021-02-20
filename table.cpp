#include "table.h"

/** Acquires a cell, which is requested by provided address
 *
 * @param address of a requested cell in a csv table
 * @return the content of a requested cell
 */
string Table ::get_cell(const string& address) const {
    istringstream iss(address);
    string col_name, pos;
    col_name = address.substr(0,address.find_first_of("0123456789"));
    pos = address.substr(address.find_first_of("0123456789"), string::npos);

    auto it = find(table.at("r_h").begin(), table.at("r_h").end(), pos);
    int index = it - table.at("r_h").begin();
    string cell = table.at(col_name)[index];

    return cell;
}

/** Calculates the desired mathematical expression
 *
 * @param expression to be calculated
 * @return the result of a calculated expression
 */
int Table ::calculate(const string& expression) const {
    size_t i = expression.find_first_of("+-*/");
    char op = expression.at(i);
    istringstream iss(expression);

    string arg1, arg2;
    getline(iss, arg1, op);
    getline(iss, arg2, op);

    int val1 = stoi(get_cell(arg1));
    int val2 = stoi(get_cell(arg2));

    switch (op) {
        case '+':
            return val1 + val2;
        case '-':
            return val1 - val2;
        case '*':
            return val1 * val2;
        case '/':
            return val1 / val2;
    }
}
