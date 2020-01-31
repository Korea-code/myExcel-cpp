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
    
//    NumNode* current;
//    NumNode start;
NumStack::NumStack() : start(nullptr, 0){
        current = &start;
    }

// Push one element on the top
void NumStack::push(double _number){
    NumNode* next = new NumNode(current, _number);
    current = next;
}

// remove top and return
double NumStack::pop(){
    if(!is_empty()){
        double temp = current->number;
        NumNode *node_temp = current;
        current = node_temp->prev;
        delete node_temp;
        return temp;
    }else
        return start.number; // 0
    
    
}

// return the top
double NumStack::peek(){
    return current->number;
}

// check the stack is empty
bool NumStack::is_empty(){
    if(current != &start)
        return false;
    else
        return true;
}

NumStack::~NumStack(){
    while(!is_empty()){
        NumNode* temp = current;
        current = current->prev;
        delete temp;
    }

}
