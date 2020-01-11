//
//  main.cpp
//  myExcel
//
//  Created by 김지효 on 2020-01-03.
//  Copyright © 2020 김지효. All rights reserved.
//  Basic structure from https://modoocode.com/

#include <iostream>
#include <fstream>
#include "Table.hpp"
using namespace MyExcel;
int main() {
    TextTable table(5, 5);
    std::ofstream out("TableTest....txt");

    table.reg_cell(new Cell("Hello~", 0, 0, &table), 0, 0);
    table.reg_cell(new Cell("C++", 0, 1, &table), 0, 1);

    table.reg_cell(new Cell("Programming", 1, 1, &table), 1, 1);
    table.reg_cell(new Cell("Test!!", 4, 4, &table), 4, 4);
    std::cout << std::endl << table;
    out << table;
}
