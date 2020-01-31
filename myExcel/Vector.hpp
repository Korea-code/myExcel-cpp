//
//  Vector.hpp
//  myExcel
//
//  Created by 김지효 on 2020-01-06.
//  Copyright © 2020 김지효. All rights reserved.
//
#include <iostream>
#include <string>


using namespace std;
#ifndef Vector_hpp
#define Vector_hpp
template <typename T>
class Vector {
  T* data;
  int capacity; // total capacity
  int length;   // current string length

 public:
    Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}

  // adding one element at last
    void push_back(T s){
        if (capacity <= length) {
            //If capacity is not enough, expand it twice.
            T* temp = new T[capacity * 2];
            for (int i = 0; i < length; i++) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            capacity *= 2;
        }
        data[length] = s;
        length++;
    }

  // access to element by index
  T operator[](int i)const { return data[i]; }

  // remove one element
  void remove(int x) {
      for (int i = x + 1; i < length; i++) {
          data[i - 1] = data[i];
      }
      length--;
  }

  // show current size of Vector
  int size()const { return length; }

  ~Vector(){
      if (data) {
          delete[] data;
      }
  }
};

template <>
class Vector<bool> {
    unsigned int* data;
    int capacity;
    int length;
public:
    typedef bool value_type;
    
    Vector(int n = 1) : data(new unsigned int[n / 32 + 1]), capacity(n / 32 + 1), length(0){
        for(int i = 0; i < capacity; ++i)
            data[i] = 0;
    }
    void push_back(bool s) {
        if(capacity * 32 < length){
            unsigned int* temp = new unsigned int[capacity * 2];
            
            for(int i = 0; i < capacity * 2; ++i){
                if(i < capacity)
                    temp[i] = data[i];
                else
                    temp[i] = 0;
            }
            capacity *= 2;
            delete [] data;
            data = temp;
            temp = nullptr;
        }
        if(s) {
            data[length / 32] |= (1 << (length % 32));
        }
        ++length;
    }
    
    bool operator[](int i) {
        return data[i / 32] & (1 << (i % 32)) ? true : false;
    }
    
    void remove(int x) {
        if(x < length){
            for (int i = x + 1; i < length; ++i){
                int prev = i -1;
                if((*this)[i])
                    data[prev / 32] |= (1 << (prev%32));
                else
                    data[prev / 32] &= (0xFFFFFFFF ^ (1 << prev % 32));
            }
        }
        --length;
    }
};
#endif /* Vector_hpp */

