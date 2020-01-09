//
//  Stack.cpp
//  myExcel
//
//  Created by 김지효 on 2020-01-08.
//  Copyright © 2020 김지효. All rights reserved.
//
#include <string>
using namespace std;
#include "Stack.hpp"
Stack::Stack() : start(nullptr, ""){
    current = &start;
}

void Stack::push(string s){
    Node* next = new Node(current, s);
    current = next;
}

string Stack::pop(){
    if(current != &start){
        string temp = current->s;
        Node* temp_node = current;
        current = current->prev;
        delete temp_node;
        return temp;
    }else
        return start.s;
}

string Stack::peek(){ return current->s; }

bool Stack::is_empty(){
    if(current != &start)
        return false;
    else
        return true;
}

Stack::~Stack(){
    while(!is_empty()){
        Node* temp = current;
        current = current->prev;
        delete temp;
    }
}
