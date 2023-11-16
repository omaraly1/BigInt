//
// Created by Omar Aly on 2022-10-09.
//

#include <cmath>
#include "BigInteger.h"

BigInteger::BigInteger() {
    base = 10;
    nums.insertNum(0, 0);
    sign = true;
}

BigInteger::BigInteger(int n, int b) {
    base = b;
    sign = n >= 0;
    initializeFromDecimal(n);
}

BigInteger::BigInteger(const BigInteger &b) {
    base = b.base;
    nums = DynamicArray(b.nums);
    DynamicArray x = nums;
    sign = b.sign;
};

void BigInteger::initializeFromDecimal(int num) {

    int digit;
    num = abs(num);
    while (num > 0) {
        digit = num % base;
        nums.insertNum(digit, 0);
        num = num / base;
    }
}

int BigInteger::num_digits() const {
    return nums.length();
}

void BigInteger::add_digit(int value) {
    nums.insertNum(value, nums.length());
}

void BigInteger::add_digit(char value) {
    add_digit(convertToInt(value));
}

void BigInteger::insert_digit(int value, int index) {
    if (index == 0 && value == 0) return;
    if (index < 0 || index >= num_digits()) return;
    if (nums.length() == 1 && nums[0] == 0) {
        nums[0] = value;
        return;
    }
    nums.insertNum(value, index);
}

void BigInteger::insert_digit(char value, int index) {
    insert_digit(convertToInt(value), index);
}

void BigInteger::remove_digit() {
    nums.removeNum();
}

int BigInteger::operator[](int index) const {
    return nums[index];
}

char BigInteger::getChar(int index) {
    return convertToChar(nums[index]);
}

BigInteger &BigInteger::operator=(const BigInteger &b) {
    base = b.base;
    nums = DynamicArray(b.nums);
    sign = b.sign;
    return (*this);
}

BigInteger BigInteger::convertToBase(int baseOut) const {

    BigInteger result;
    result.base = baseOut;
    result.sign = sign;

    for (int i = 0; i < num_digits(); i++) {

        for (int j = 0; j < result.num_digits(); j++) {
            result.nums[j] *= base;
        }

        result.nums[0] += nums[i];

        for (int x = 0; x < result.num_digits(); x++) {

            if (result.nums[x] > baseOut - 1) {

                int temp = result.nums[x] / baseOut;
                if (temp > 0) {

                    if (x + 1 >= result.num_digits()) {
                        result.add_digit(0);
                    }
                    result.nums[x + 1] += temp;
                }
            }
            result.nums[x] %= baseOut;
        }

    }
    result.nums.reverse();

    return result;
}

BigInteger BigInteger::multiplyBase10(const BigInteger &b) {

    BigInteger result;
    result.remove_digit();
    result.base = 10;
    result.sign = true;

    for (int i = num_digits() - 1; i >= 0; i--) {
        int remainder = 0;
        BigInteger temp;
        temp.remove_digit();
        int newDigit = nums[i] * pow(10, num_digits() - i - 1);
        for (int j = b.num_digits() - 1; j >= 0; j--) {
            int sum = newDigit * b.nums[j] + remainder;
            if (sum > 9) {
                remainder = sum / 10;
                sum %= 10;
            } else remainder = 0;
            temp.add_digit(sum);
        }

        if (remainder != 0) {
            temp.add_digit(remainder);
        }

        temp.nums.reverse();
        result = result + temp;

    }
    result.sign = sign == b.sign;
    return result;

}

BigInteger BigInteger::addBase10(const BigInteger &b) {

    BigInteger result;
    result.remove_digit();
    int longest = max(num_digits(), b.num_digits());
    int arr1[longest];
    int arr2[longest];
    result.base = 10;
    result.sign = sign;

    for (int i = 0; i < longest; i++) {
        if (i < num_digits()) {
            arr1[i] = nums[num_digits() - i - 1];
        } else arr1[i] = 0;
        if (i < b.num_digits()) {
            arr2[i] = b.nums[b.num_digits() - i - 1];
        } else arr2[i] = 0;
    }

    int remainder = 0;
    for (int i = 0; i < longest; i++) {
        int sum = arr1[i] + arr2[i] + remainder;
        if (sum > 9) {
            remainder = sum / 10;
            sum %= 10;
        } else remainder = 0;
        result.add_digit(sum);
    }
    if (remainder != 0) {
        result.add_digit(remainder);
    }

    result.trimLeadingZeros();
    result.nums.reverse();
    return result;

}

bool BigInteger::operator==(const BigInteger &b) {
    if (getSign() != b.getSign()) return false;
    BigInteger num1base10 = convertToBase(10);
    BigInteger num2base10 = b.convertToBase(10);

    if (num1base10.num_digits() != num2base10.num_digits()) return false;

    for (int i = 0; i < num1base10.num_digits(); i++) {
        if (num1base10[i] != num2base10[i]) return false;
    }
    return true;
}

bool BigInteger::operator!=(const BigInteger &b) {
    return !(*this == b);
}

bool BigInteger::operator<(const BigInteger &b) {

    if (getSign() != b.getSign()) {
        return !getSign();
    }
    BigInteger num1base10 = convertToBase(10);
    BigInteger num2base10 = b.convertToBase(10);

    if (num1base10.num_digits() < num2base10.num_digits()) {
        return true;
    } else if (num1base10.num_digits() == num2base10.num_digits()) {

        for (int i = 0; i < num1base10.num_digits(); i++) {
            if ((num1base10.nums[i]) < (num2base10.nums[i])) {
                return true;
            }
            if (num1base10.nums[i] > num2base10.nums[i]) {
                return false;
            }
        }
    }
    return false;
}

bool BigInteger::operator>(const BigInteger &b) {
    return !(*this <= b);
}

bool BigInteger::operator<=(const BigInteger &b) {
    return (*this < b) || (*this == b);
}

bool BigInteger::operator>=(const BigInteger &b) {
    return (*this > b) || (*this == b);
}

BigInteger BigInteger::operator++() {
    BigInteger one(1, 10);
    *this = *this + one;
    return *this;
}

BigInteger BigInteger::operator--() {
    BigInteger one(1, 10);
    *this = *this - one;
    return *this;
}

BigInteger BigInteger::operator--(int a) {
    return --(*this);
}

BigInteger BigInteger::operator++(int a) {
    BigInteger result = *this;
    BigInteger one(1, 10);
    *this = *this + one;
    return result;
}

BigInteger BigInteger::subtractBase10(const BigInteger &b) {
    BigInteger result;
    result.remove_digit();
    const BigInteger *bigger = this;
    const BigInteger *smaller = &b;

    if (bigger->num_digits() < smaller->num_digits()) {
        bigger = &b;
        smaller = this;
    } else if (bigger->num_digits() == smaller->num_digits()) {

        for (int i = 0; i < bigger->num_digits(); i++) {
            if ((bigger->nums[i]) > (smaller->nums[i])) {
                break;
            }
            if (bigger->nums[i] < smaller->nums[i]) {
                bigger = &b;
                smaller = this;
                break;
            }
        }
    }

    result.sign = bigger->sign;

    int longest = max(bigger->num_digits(), smaller->num_digits());
    int arr1[longest];
    int arr2[longest];
    result.base = 10;

    for (int i = 0; i < longest; i++) {
        if (i < bigger->num_digits()) {
            arr1[i] = bigger->nums[bigger->num_digits() - i - 1];
        } else arr1[i] = 0;
        if (i < smaller->num_digits()) {
            arr2[i] = smaller->nums[smaller->num_digits() - i - 1];
        } else arr2[i] = 0;
    }

    int borrow = 0;
    for (int i = 0; i < longest; i++) {

        if (arr2[i] > arr1[i]) {
            borrow = 10;
            arr1[i + 1]--;
        } else {
            borrow = 0;
        }
        result.add_digit(abs(arr1[i] - arr2[i] + borrow));
    }

    result.trimLeadingZeros();
    result.nums.reverse();


    return result;
}

void BigInteger::trimLeadingZeros() {
    while (num_digits() > 1 && nums[num_digits() - 1] == 0) {
        remove_digit();
    }
}


BigInteger BigInteger::operator+(const BigInteger &b) {
    BigInteger result;
    BigInteger num1base10 = convertToBase(10);
    BigInteger num2base10 = b.convertToBase(10);

    if (sign != b.sign) result = num1base10.subtractBase10(num2base10);
    else result = num1base10.addBase10(num2base10);
    result = result.convertToBase(base);
    return result;

}

BigInteger BigInteger::operator-(const BigInteger &b) {

    BigInteger result;
    BigInteger flip(b);

    flip.sign = !b.sign;

    result = *this + flip;
    return result;

}


BigInteger BigInteger::operator*(const BigInteger &b) {
    BigInteger num1base10 = convertToBase(10);
    BigInteger num2base10 = b.convertToBase(10);
    return num1base10.multiplyBase10(num2base10).convertToBase(base);

}


BigInteger BigInteger::operator/(const BigInteger &b) {
    BigInteger num1base10 = convertToBase(10);
    BigInteger num2base10 = b.convertToBase(10);

    num1base10.sign = true;
    num2base10.sign = true;
    bool finalSign = getSign() == b.getSign();

    BigInteger result;
    result.base = base;

    while(num1base10 >= num2base10){
        num1base10 = num1base10 - num2base10;
        result++;
    }
    result.sign = finalSign;
    return result;
}

BigInteger BigInteger::operator%(const BigInteger &b) {
    BigInteger num1base10 = convertToBase(10);
    BigInteger num2base10 = b.convertToBase(10);
    num1base10.sign = true;
    num2base10.sign = true;
    bool finalSign = !(getSign() == b.getSign());

    BigInteger result;
    result.base = base;

    while(num1base10 >= num2base10){
        num1base10 = num1base10 - num2base10;
    }
    result = result + num1base10;
    result.sign = finalSign;
    return result;
}

bool BigInteger::getSign() const {
    if (num_digits() == 0 || num_digits() == 1 && nums[0] == 0) return true;
    return sign;
}

ostream &operator<<(ostream &out, const BigInteger &n) {
    if (!n.getSign()) out << "-";
    for (int i = 0; i < n.num_digits(); i++) {
        out << (BigInteger::convertToChar(n[i]));
    }
    return out;
}

istream& operator>>(istream &in, BigInteger &n) {

    std::string input;
    std::string base;
    in >> input;
    in >> base;
    n.base = stoi(base);
    int i = 0;
    n.sign = true;

    if (input[i] == '-') {
        n.sign = false;
        i++;
    }
    n.remove_digit();
    for (; i < input.length(); i++) {
        n.add_digit(BigInteger::convertToInt(input[i]));
    }
    return in;
}

char BigInteger::convertToChar(int digit) {

    char result;
    char zero = '0';
    char a = 'A';

    if (digit < 10) {
        result = (char) ((int) zero + digit);
        return result;
    }
    result = (char) ((int) a + digit - 10);
    return result;
}

int BigInteger::convertToInt(char c) {

    int zero = (int) '0';
    int a = (int) 'A';

    if (c <= '9') return ((int) c - zero);

    return ((int) c - a + 10);
}




