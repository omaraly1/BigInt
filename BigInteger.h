//
// Created by Omar Aly on 2022-10-09.
//

#ifndef A1_BIGINTEGER_H
#define A1_BIGINTEGER_H


#include <iostream>
#include "DynamicArray.h"
using namespace std;

class BigInteger
{
private:
    int base;
    bool sign;
    DynamicArray nums;
    void initializeFromDecimal(int);
public:
    BigInteger();
    BigInteger(int, int);
    BigInteger(const BigInteger& b);
    int num_digits() const;
    void add_digit(int value);
    void add_digit(char value);
    void remove_digit();
    void insert_digit(int value, int index);
    void insert_digit(char value, int index);
    int operator[](int index) const;
    char getChar(int index);
    BigInteger& operator=(const BigInteger& b);
    bool operator!=(const BigInteger& b);
    bool operator==(const BigInteger& b);
    bool operator>(const BigInteger& b);
    bool operator<(const BigInteger& b);
    bool operator>=(const BigInteger& b);
    bool operator<=(const BigInteger& b);
    BigInteger operator+(const BigInteger& b);
    BigInteger operator-(const BigInteger& b);
    BigInteger operator*(const BigInteger &b);
    BigInteger operator/(const BigInteger &b);
    BigInteger operator%(const BigInteger &b);
    friend ostream& operator <<(ostream&, const BigInteger&);
    friend istream& operator >>(istream&,  BigInteger&);
    BigInteger operator++();
    BigInteger operator++(int a);
    BigInteger operator--();
    BigInteger operator--(int a);

    //Helper methods
    void trimLeadingZeros();
    static char convertToChar(int digit);
    static int convertToInt(char c);
    BigInteger convertToBase(int baseOut) const;
    BigInteger multiplyBase10(const BigInteger& b);
    BigInteger subtractBase10(const BigInteger &b);
    BigInteger addBase10(const BigInteger &b);
    bool getSign() const;
};



#endif //A1_BIGINTEGER_H
