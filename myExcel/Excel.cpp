//
//  Excel.cpp
//  myExcel
//
//  Created by 김지효 on 2020-01-31.
//  Copyright © 2020 김지효. All rights reserved.
//
#include <iostream>
#include <fstream>
#include "Excel.hpp"
namespace myExcel{
Excel::Excel(int max_col, int max_row, int choice){
    switch (choice) {
        case TEXT_TABLE:
            current_table = new TextTable(max_col, max_row);
            break;
        case CSV_TABLE:
            current_table = new CSVTable(max_col, max_row);
        default:
            current_table = new HTMLTable(max_col, max_row);
            break;
    }
}
   
int Excel::parse_user_input(string s){
    int next = 0, strlen = static_cast<int>(s.length());
    string command = "";
    for (int i = 0; i < strlen; ++i){
        if(s[i] == ' ') {
            command = s.substr(0, i);
            next = i + 1;
            break;
        }else if(i == strlen - 1){
            command = s.substr(0, i + 1);
            next = i + 1;
            break;
        }
    }
    
    string to = "";
    for (int i = next; i < strlen; ++i){
        if(s[i] == ' ' || i == strlen - 1){
            to = s.substr(next, i - next);
            next = i + 1;
            break;
        }else if(i == strlen - 1) {
            to = s.substr(0, i + 1);
            next = i + 1;
            break;
        }
    }
    int row = to[0] - 'A';
    int col = atoi(to.c_str() + 1) - 1;
    
    string rest = s.substr(next);
    
    if (command == "sets")
        current_table->reg_cell(new StringCell(rest, col, row, current_table), col, row);
    else if (command == "setn")
        current_table->reg_cell(new NumberCell(atoi(rest.c_str()), col, row, current_table), col, row);
    else if (command == "setd")
        current_table->reg_cell(new DateCell(rest, col, row, current_table), col, row);
    else if (command == "sete")
        current_table->reg_cell(new ExprCell(rest, col, row, current_table), col, row);
    else if (command == "out") {
        ofstream out(to);
        out << *current_table;
        std::cout << "Table is saved in "<< to << std::endl;
    } else if (command == "exit")
        return 0;
    
    return 1;
}

void Excel::command_line() {
    string s;
    std::getline(cin, s);
    while (parse_user_input(s)){
        std::cout << *current_table << std::endl << ">> ";
        getline(cin, s);
    }
}

}
