//
//  Stack.hpp
//  myExcel
//
//  Created by 김지효 on 2020-01-08.
//  Copyright © 2020 김지효. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <string>

class Node {
public:
    Node* prev;
    string s;

    Node(Node* prev, string s) : prev(prev), s(s) {}
};

class Stack {
    Node* current;
    Node start;

public:
    Stack();

    // Push one element on the top
    void push(string s);

    // remove top and return
    string pop();

    // return the top
    string peek();

    // check the stack is empty
    bool is_empty();

    ~Stack();
};

class NumNode {
public:
    NumNode* prev;
    double number;

    NumNode(NumNode* prev, double number) : prev(prev), number(number) {}
};

class NumStack {
    NumNode* current;
    NumNode start;

public:
    NumStack();

    // Push one element on the top
    void push(double s);

    // remove top and return
    double pop();

    // return the top
    double peek();

    // check the stack is empty
    bool is_empty();

    ~NumStack();
};
#endif /* Stack_hpp */
