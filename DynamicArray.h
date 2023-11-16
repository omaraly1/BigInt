//
// Created by Omar Aly on 2022-10-16.
//

#ifndef A1_DYNAMICARRAY_H
#define A1_DYNAMICARRAY_H


class DynamicArray {
private:
    int *nums;
    int numDigits;
    int size;

public:
    DynamicArray();

    ~DynamicArray();

    DynamicArray(const DynamicArray &);

    int length() const;

    void reverse();

    void removeNum();

    void insertNum(int value, int index);

    int &operator[](int) const;

    DynamicArray &operator=(const DynamicArray &d);
};


#endif //A1_DYNAMICARRAY_H
