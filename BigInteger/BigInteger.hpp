#ifndef BIGINTEGER_HPP
#define BIGINTEGER_HPP
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stdexcept>

class BigInteger {
public:
    BigInteger();
    BigInteger(int value);
    BigInteger(std::string value);
    BigInteger(const char* value); // added constructor for const char* (string literal
    BigInteger(const BigInteger& other);
    BigInteger& operator=(const BigInteger& other);
    BigInteger operator+(const BigInteger& other) const;
    BigInteger operator-(const BigInteger& other) const;
	BigInteger operator-() const;
    BigInteger operator*(const BigInteger& other) const;
    BigInteger operator/(const BigInteger& other) const;
    BigInteger operator%(const BigInteger& other) const;
    bool operator==(const BigInteger& other) const;
    bool operator!=(const BigInteger& other) const;
    bool operator<(const BigInteger& other) const;
    bool operator>(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;
    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other);
	BigInteger operator^(const BigInteger& other);
    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);
    std::string toString() const;
    int toInt() const;
    bool getIsNegative() const;
    void setNegative(bool isNegative);
    BigInteger abs() const;
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bigInteger);
    friend std::istream& operator>>(std::istream& is, BigInteger& bigInteger);

private:
    std::vector<int> digits;
    bool isNegative = false;
};

BigInteger max(const BigInteger& a, const BigInteger& b);
BigInteger min(const BigInteger& a, const BigInteger& b);
BigInteger abs(const BigInteger& a);
BigInteger pow(const BigInteger& base, const BigInteger& exponent);
BigInteger sqrt(const BigInteger& a);
BigInteger gcd(const BigInteger& a, const BigInteger& b);
BigInteger lcm(const BigInteger& a, const BigInteger& b);
BigInteger factorial(const BigInteger& a);
BigInteger modPow(const BigInteger& base, const BigInteger& exponent, const BigInteger& mod);
#endif