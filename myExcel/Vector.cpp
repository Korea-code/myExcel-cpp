//
//  Vector.cpp
//  myExcel
//
//  Created by 김지효 on 2020-01-06.
//  Copyright © 2020 김지효. All rights reserved.
//
//
//Vector::Vector(int n) : data(new string[n]), capacity(n), length(0) {}
//void Vector::push_back(string s) {
//    if (capacity <= length) {
//        //If capacity is not enough, expand it twice.
//        string* temp = new string[capacity * 2];
//        for (int i = 0; i < length; i++) {
//            temp[i] = data[i];
//        }
//        delete[] data;
//        data = temp;
//        capacity *= 2;
//    }
//    data[length] = s;
//    length++;
//}
//
//string Vector::operator[](int i)const { return data[i]; }
//
//void Vector::remove(int x) {
//    for (int i = x + 1; i < length; i++) {
//        data[i - 1] = data[i];
//    }
//    length--;
//}
//
//int Vector::size()const { return length; }
//
//Vector::~Vector() {
//    if (data) {
//        delete[] data;
//    }
//}
