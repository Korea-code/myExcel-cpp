//
//  Excel.hpp
//  myExcel
//
//  Created by 김지효 on 2020-01-31.
//  Copyright © 2020 김지효. All rights reserved.
//

#ifndef Excel_hpp
#define Excel_hpp
#include "Table.hpp"
namespace myExcel{

const int TEXT_TABLE = 0;
const int CSV_TABLE = 1;


class Table;
class Excel {
    Table* current_table;
public:
    Excel(int max_col, int max_row, int choice = TEXT_TABLE);
    
    int parse_user_input(string s);
    void command_line();
    
};
}
#endif /* Excel_hpp */
