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
  // 생성자
  Vector(int n = 1);

  // 맨 뒤에 새로운 원소를 추가한다.
  void push_back(string s);

  // 임의의 위치의 원소에 접근한다.
  string operator[](int i);

  // x 번째 위치한 원소를 제거한다.
  void remove(int x);

  // 현재 벡터의 크기를 구한다.
  int size();

  ~Vector();
};
#endif /* Vector_hpp */
