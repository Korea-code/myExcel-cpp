//
//  Table.hpp
//  myExcel
//
//  Created by 김지효 on 2020-01-03.
//  Copyright © 2020 김지효. All rights reserved.
//  Basic structure from https://modoocode.com/215


#ifndef Table_hpp
#define Table_hpp


#include <iostream>
#include <string>
#include "Cell.hpp"


namespace myExcel {
class Cell;
class Table {
protected:
    int max_col_size, max_row_size;
    Cell*** data_base;
    
public:
    Table(int max_col, int max_row);
    ~Table();
    
    void reg_cell(Cell* c, int col, int row);  // register a cell
    std::string get_cell(int col, int row);  // get cell in the position
    
    int to_numeric(const std::string& cell_name);
    int to_numeric(int col, int row);
    
    std::string stringify(const std::string cell_name);
    std::string stringify(int col, int row);
    
    virtual std::string print_table()const = 0;
};

std::ostream& operator<<(std::ostream&, Table&);

// for .txt files
class TextTable : public Table {
    std::string repeat_char(int num, char ch)const;
    
    // convert 0 -> A, 1 -> B ... AA, AB ...
    std::string col_num_to_str(int n)const;
public:
    TextTable(int col, int row);
    
    std::string print_table()const;
};
class CSVTable : public Table {
public:
    CSVTable(int col, int row);
    std::string print_table()const;
};
class HTMLTable : public Table {
public:
    HTMLTable(int col, int row);
    
    std::string print_table()const;
};
}
#endif /* Table_hpp */
