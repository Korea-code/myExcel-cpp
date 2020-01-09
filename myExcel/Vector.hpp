//
//  Vector.hpp
//  myExcel
//
//  Created by 김지효 on 2020-01-06.
//  Copyright © 2020 김지효. All rights reserved.
//
#include <string>
using namespace std;
#ifndef Vector_hpp
#define Vector_hpp

class Vector {
  string* data;
  int capacity; // total capacity
  int length;   // current string length

 public:
  Vector(int n = 1);

  // adding one element at last
  void push_back(string s);

  // access to element by index
  string operator[](int i)const;

  // remove one element
  void remove(int x);

  // show current size of Vector
  int size()const;

  ~Vector();
};
#endif /* Vector_hpp */
