//
//  main.cpp
//  myExcel
//
//  Created by 김지효 on 2020-01-03.
//  Copyright © 2020 김지효. All rights reserved.
//  Basic structure from https://modoocode.com/

#include <iostream>
#include <fstream>
#include "Excel.hpp"
#include "Table.hpp"
#include "Cell.hpp"
using namespace myExcel;
int main() {
    std::cout << "Please Enter | (type) (max column) (max row) |" << std::endl;
    std::cout << "Type : 1 - Text Table  2 - CSV Table  3 - HTML Table" << std::endl << " >> ";
    
    int type, max_col, max_row;
    std::cin >> type >> max_row >> max_col;
    Excel m(max_col, max_row, type - 1);
    std::cout << "Command format : (set) (position) (data)" << std::endl
    <<"set mode : sets(string), setn(integer), setd(yyyy-mm-dd), sete(Exper)" << std::endl;
    
    m.command_line();
}
