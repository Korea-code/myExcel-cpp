//
//  Table.cpp
//  myExcel
//
//  Created by 김지효 on 2020-01-03.
//  Copyright © 2020 김지효. All rights reserved.
//
#include <iostream>
#include <string>
#include "Table.hpp"

using namespace std;
namespace MyExcel {
Cell::Cell(string data, int x, int y, Table* table): data(data), x(x), y(y), table(table){}

string Cell::stringify(){
    return data;
}

int Cell::to_numeric(){
    return 0;
}
// initial max_row * max_col size table. initial value is nullptr
Table::Table(int max_col, int max_row): max_col_size(max_col), max_row_size(max_row){
    data_base = new Cell**[max_col_size];
    for(int i = 0; i < max_row_size; ++i){
        data_base[i] = new Cell*[max_row_size];
        for(int j = 0; j< max_row_size; ++j)
            data_base[i][j] = nullptr;
    }
}
Table::~Table(){
    for(int i = 0; i < max_col_size; ++i){
        for(int j = 0; j < max_row_size; ++j){
            if(data_base[i][j] != nullptr)
                delete data_base[i][j];
        }
        delete [] data_base[i];
    }
    delete [] data_base;
}

void Table::reg_cell(Cell* c, int col, int row){
    if(max_col_size <= col || max_row_size <= row) return; // because col and row is index. so it must be smaller than max - 1
    
    if(data_base[col][row]) delete data_base[col][row];  // deallocate for save data
    
    data_base[col][row] = new Cell(c->stringify(), col, row, this);
    
    // if 'c' is created for this table deallocte it
    if(c->table == this) delete c;
}

string Table::get_cell(int col, int row){
    return data_base[col][row]->data;
}

int Table::to_numeric(const string& cell_name){
    int col = cell_name[0] - 'A';
    int row = atoi(cell_name.c_str() + 1) - 1;
    
    if(col < max_col_size && row < max_row_size)
        if(data_base[col][row])
            return data_base[col][row]->to_numeric();
    return 0;
}
int Table::to_numeric(int col, int row){
    if(col < max_col_size && row < max_row_size)
        if(data_base[col][row]) return data_base[col][row]->to_numeric();
    return 0;
}

string Table::stringify(const string cell_name){
    int col = cell_name[0] - 'A';
    int row = atoi(cell_name.c_str() + 1) - 1;
    
    if(col < max_col_size && row < max_row_size)
        if(data_base[col][row])
            return data_base[col][row]->stringify();
    return "";
}
string Table::stringify(int col, int row){
    if(col < max_col_size && row < max_row_size)
        if(data_base[col][row]) return data_base[col][row]->stringify();
    return "";
}

ostream& operator<<(ostream& os, Table& table){
    os << table.print_table();
    return os;
}


TextTable::TextTable(int col, int row): Table(col, row){}

string TextTable::repeat_char(int num, char ch)const{
    string temp = "";
    for(int i = 0; i < num; ++i) temp.push_back(ch);
    return temp;
}
    
    // convert 0 -> A, 1 -> B ... AA, AB ...
string TextTable::col_num_to_str(int n)const{
    string temp = "";
    char ch = 'A';
    for(int i = 0; i < n; ++i){
        if(ch == 'Z') {
            ch = 'A';
            temp.push_back(ch);
        }else{
            ++ch;
        }
    }
    temp.push_back(ch);
    return temp;
}

string TextTable::print_table()const{
    string total_table;
    int* row_max_wide = new int[max_row_size];
    
    for (int i = 0; i < max_row_size; ++i){
        unsigned max_wide = 2;
        for(int j = 0; j < max_col_size; ++j) {
            if(data_base[j][i] && data_base[j][i]->stringify().length() > max_wide)
                max_wide = data_base[j][i]->stringify().length();
        }
        row_max_wide[i] = max_wide;
    }
    
    total_table += "    ";
    int total_wide = 4;
    for(int i = 0; i < max_row_size; ++i){
        if(row_max_wide[i]){
            int max_len = 2 > row_max_wide[i] ? 2 : row_max_wide[i];
            total_table += " | " + col_num_to_str(i);
            total_table += repeat_char(max_len - col_num_to_str(i).length(), ' ');
            total_wide += (max_len + 3);
        }
    }
    
    total_table += "\n";
    
    for(int i = 0; i < max_col_size; ++i){
        total_table += repeat_char(total_wide, '-');
        total_table += "\n" + to_string(i + 1);
        total_table += repeat_char(4 - to_string(i + 1).length(), ' ');
        
        for(int j = 0; j < max_row_size; ++j) {
            if(row_max_wide[j]) {
                int max_len = 2 > row_max_wide[j] ? 2 : row_max_wide[j];
                
                string s = "";
                if(data_base[i][j])
                    s = data_base[i][j]->stringify();
                total_table += " | " + s;
                total_table += repeat_char(max_len - s.length(), ' ');
            }
        }
        total_table += "\n";
    }
    return total_table;
}

}



