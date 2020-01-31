//
//  Cell.hpp
//  myExcel
//
//  Created by 김지효 on 2020-01-30.
//  Copyright © 2020 김지효. All rights reserved.
//


#ifndef Cell_hpp
#define Cell_hpp
#include <string>
#include "Table.hpp"
#include "Vector.hpp"

namespace myExcel {
class Table;
class Cell {
protected:
    Table* table;  // Where is this table belonging
    int x, y;  // colomn and row
public:
    Cell(int x, int y, Table* table);
    virtual std::string stringify() = 0;
    virtual int to_numeric() = 0;
    virtual ~Cell(){}
};

//Derived class which can save string data;
class StringCell : public Cell {
    std::string data;
public:
    std::string stringify();
    int to_numeric();
    ~StringCell(){};
    StringCell(std::string data, int x, int y, Table* t);
};
//Derived class which can save int data
class NumberCell : public Cell {
    int data;
    
public:
    std::string stringify();
    int to_numeric();
    ~NumberCell(){}
    NumberCell(int data, int x, int y, Table* t);
};

//Derived class which can save date(time_t)
class DateCell : public Cell{
    time_t data;
    
public:
    std::string stringify();
    int to_numeric();
    
    ~DateCell(){}
    // string input format is yyyy-mm-dd
    DateCell(std::string s, int x, int y, Table* t);
};

//Derived Class which can calculate value;
class ExprCell : public Cell {
    std::string data;
    std::string* parsed_expr;
    
    Vector exp_vec;
    
    // Return Operator Priority
    int precedence(char c);
    
    // Parse expression to make postfix notation
    void parse_expression();
    
public:
    ExprCell(std::string data, int x, int y, Table* t);
    std::string stringify();
    int to_numeric();
    ~ExprCell(){}
};

}
#endif /* Cell_hpp */
