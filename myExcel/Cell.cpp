//
//  Cell.cpp
//  myExcel
//
//  Created by 김지효 on 2020-01-30.
//  Copyright © 2020 김지효. All rights reserved.
//
#include <string>
#include <ctime>
#include "Cell.hpp"
#include "Stack.hpp"
using namespace std;
namespace myExcel {

Cell::Cell(int x, int y, Table* table): x(x), y(y), table(table){}

//StringCell
StringCell::StringCell(string data, int x, int y, Table* t): Cell(x, y, t), data(data){}

string StringCell::stringify(){
    return data;
}

int StringCell::to_numeric(){
    return 0;
}



// Number Cell


NumberCell::NumberCell(int data, int x, int y, Table* t): Cell(x, y, t), data(data){}

string NumberCell::stringify(){
    return to_string(data);
}
int NumberCell::to_numeric(){
    return data;
}


//Date Cell

// string input format is yyyy-mm-dd
DateCell::DateCell(std::string s, int x, int y, Table* t): Cell(x, y, t) {
    int year = atoi(s.c_str());
    int month = atoi(s.c_str() + 5);
    int day = atoi(s.c_str() + 8);
    
    tm temp;
    temp.tm_year = year - 1900;
    temp.tm_mon = month - 1;
    temp.tm_mday = day;
    temp.tm_hour = 0;
    temp.tm_min = 0;
    temp.tm_sec = 0;
    
    data = mktime(&temp);
}

string DateCell::stringify(){
    char buffer[50];
    tm temp;
    
    localtime_r(&data, &temp);
    // %F to convert yyyy-mm-dd format
    strftime(buffer, 50, "%F", &temp);
    return string(buffer);
}
int DateCell::to_numeric(){
    return static_cast<int>(data);
}


// ExprCell


    // Return Operator Priority
int ExprCell::precedence(char c){
    switch (c) {
        case '(':
        case '[':
        case '{':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
            
//    // for convenience
//        case ')':
//        case ']':
//        case '}':
//            return -1;
    }
    return 0;
}
    
    // Parse expression to make postfix notation
void ExprCell::parse_expression(){
    
    Stack stack;
    
    // enclose by parenthesis
    data.insert(0, "(");
    data.push_back(')');
    
    
    for(int i = 0; i < data.length(); ++i){
        // one letter alphabet and single number
        if(isalpha(data[i]))
            exp_vec.push_back(data.substr(i++, 2));
        else if(isdigit(data[i]))
            exp_vec.push_back(data.substr(i, 1));
        else if(data[i] == '(' || data[i] == '[' || data[i] == '{')
            stack.push(data.substr(i, 1));
        else if(data[i] == ')' || data[i] == ']' || data[i] == '}') {
            string t = stack.pop();
            while(t != "(" && t != "[" && t != "{"){
                exp_vec.push_back(t);
                t = stack.pop();
            }
        }else if(data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/'){
            while(!stack.is_empty() &&
                  precedence(stack.peek()[0]) >= precedence(data[i])) {
                exp_vec.push_back(stack.pop());
            }
            stack.push(data.substr(i, 1));
        }
    }
    
}
    
ExprCell::ExprCell(std::string data, int x, int y, Table* t): Cell(x, y, t), data(data){
    parse_expression();
}

std::string ExprCell::stringify(){
    return to_string(to_numeric());
}


int ExprCell::to_numeric(){
    NumStack stack;

    for(int i = 0; i < exp_vec.size(); i++){
       string s = exp_vec[i];
       
       if(isalpha(s[0])) {                  // cell
           stack.push(table->to_numeric(s));
       } else if(isdigit(s[0])) {           // number
           stack.push(atoi(s.c_str()));
       } else {                             // operator
           double y = stack.pop();
           double x = stack.pop();
           switch (s[0]) {
               case '+' :
                   stack.push(x + y);
                   break;
               case '-' :
                   stack.push(x - y);
                   break;
               case '*' :
                   stack.push(x * y);
                   break;
               case '/' :
                   stack.push(x / y);
           }
       }
    }
    return stack.pop();
}


}
