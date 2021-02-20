//
// Created by HomePC on 18.02.2021.
//
#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/**
 * Implementation of a csv Table
 *
 * Stores a table in "map<string, vector<string>> table", where a key is a name of a column and value is a vector,
 * which represents this column. In order to avoid mixing columns order, we have a use of "vector<string> col_order,
 * which stores the correct representation of the order. The first column, which holds names for rows is called "r_h"
 * in current solution.
 *
 */
class Table {
public:
    /**
     * @brief Constructs table from csv file
     * @param File with comma-separated values (csv)
     */
    Table(ifstream& File){
        if (File) {
            string line, value;
            vector<pair<string, size_t>>indToCalc;
            bool first = true;

            while (File.good()) {
                getline(File, line, '\n');
                istringstream iss(line);
                if (first) {
                    while (getline(iss, value, ',')) {
                        if (value.empty()) {
                            table["r_h"] = vector<string>();
                            col_order.push_back("r_h");
                        } else {
                            table[value] = vector<string>();
                            col_order.push_back(value);
                        }
                    }
                    first = false;
                } else {
                    for (vector<string>::iterator it = col_order.begin(); it != col_order.end(); it++) {
                        getline(iss, value, ',');
                        table[*it].push_back(value);
                        if (value[0] == '=') {
                            indToCalc.push_back(make_pair(*it, table[*it].size()-1));
                        }
                    }
                }
            }
            for (vector<pair<string, size_t>>::iterator it = indToCalc.begin(); it != indToCalc.end(); it++) {
                string cell = table[it->first].at(it->second);
                table[it->first][it->second] = to_string(calculate(cell.substr(1, string::npos)));
            }
        }
    };

    friend ostream& operator<<(ostream& os, const Table& tb){
        for(vector<string>::const_iterator col_it = tb.col_order.begin(); col_it != tb.col_order.end(); col_it++){
            os << *col_it << ",";
        }
        os << endl;
        for(int i = 0; i < tb.table.at("r_h").size(); i++){
            for(vector<string>::const_iterator col_it = tb.col_order.begin(); col_it != tb.col_order.end(); col_it++){
                os << tb.table.at(*col_it)[i] << ",";
            }
            os << endl;
        }
        return os;
    }
private:
    string get_cell(const string& address) const;
    int calculate(const string& expression) const;

    map<string, vector<string>> table;
    vector<string> col_order;
};



