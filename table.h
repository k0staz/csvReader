//
// Created by HomePC on 18.02.2021.
//
#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

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
    Table(ifstream& File);

    friend ostream& operator<<(ostream& os, const Table& tb){
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
private:
    string* getCellAddress(const string& address);
    void calculateAndUpdate(string* cell, set<string> traceBack = {});
    map<string, vector<string>> table;
    vector<string> col_order;
};



