//
//  Table.hpp
//  myExcel
//
//  Created by 김지효 on 2020-01-03.
//  Copyright © 2020 김지효. All rights reserved.
//  Basic structure from https://modoocode.com/215


#include <iostream>
#include <string>
using namespace std;
#ifndef Table_hpp
#define Table_hpp

class Table;
class Cell {
protected:
    Table* table;  // Where is this table belonging
    int x, y;  // colomn and row
    string data;
public:
    Cell(string data, int x, int y, Table* table);
    virtual string stringify();
    virtual int to_numeric();
    friend Table;
};

class Table {
protected:
    int max_col_size, max_row_size;
    Cell*** data_base;
    
public:
    Table(int max_col, int max_row);
    ~Table();
    
    void reg_cell(Cell* c, int col, int row);  // register a cell
    string get_cell(int col, int row);  // get cell in the position
    
    int to_numeric(const string& cell_name);
    int to_numeric(int col, int row);
    
    string stringify(const string cell_name);
    string stringify(int col, int row);
    
    virtual string print_table() = 0;
};

ostream& operator<<(ostream&, Table&);
class TextTable : public Table {};
class CSVTable : public Table {};
class HTMLTable : public Table {};
    
#endif /* Table_hpp */
