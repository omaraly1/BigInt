//
// Created by Omar Aly on 2022-10-16.
//

#include "DynamicArray.h"
#include <iostream>

using namespace std;


DynamicArray::DynamicArray() {
    numDigits = 0;
    size = 0;
    nums = NULL;
}

DynamicArray::~DynamicArray() {
    delete[]nums;
}

DynamicArray::DynamicArray(const DynamicArray &d) {
    size = d.size;
    numDigits = d.numDigits;

    if (size == 0) {
        nums = NULL;
        return;
    }

    nums = new int[size];
    for (int i = 0; i < numDigits; i++) {
        nums[i] = d.nums[i];
    }
}

void DynamicArray::insertNum(int value, int index) {

    if (numDigits == size) {
        int *new_arr = new int[size + 1];

        for (int i = 0; i < size; i++) {
            new_arr[i] = nums[i];
        }

        size++; //changed if doing bucket increments
        delete[] nums;
        nums = new_arr;
    }
    numDigits++;
    for (int i = numDigits - 1; i >= index; i--) {
        nums[i] = nums[i - 1];
    }
    nums[index] = value;
}

void DynamicArray::reverse() {


    if (size == 0) return;

    for (int i = 0; i < numDigits / 2; i++) {
        int temp = nums[numDigits - i - 1];
        nums[numDigits - i - 1] = nums[i];
        nums[i] = temp;
    }

}

void DynamicArray::removeNum() {
    numDigits--;
}

int DynamicArray::length() const {
    return numDigits;
}

int &DynamicArray::operator[](int index) const {
    if (index < 0 || index >= length()) {
        cout << "Index out of range!" << endl;
        exit(0);
    }
    return nums[index];
}

DynamicArray &DynamicArray::operator=(const DynamicArray &d) {
    size = d.size;
    numDigits = d.numDigits;

    if (size == 0) {
        nums = NULL;
        return (*this);
    }

    nums = new int[size];
    for (int i = 0; i < numDigits; i++) {
        nums[i] = d.nums[i];
    }
    return (*this);
}
