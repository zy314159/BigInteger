#include "BigInteger.hpp"

// default constructor
BigInteger::BigInteger() {
    this->isNegative = false;
    return;
}

// assign constructor for integer
BigInteger::BigInteger(int value) {
    if (value < 0) {
        this->isNegative = true;
        value = -value;
    }

    while (value) {
        digits.push_back(value % 10);
        value /= 10;
    }

    if (digits.empty()) {
        this->isNegative = false;
    }
    return;
}

// assign constructor for string
BigInteger::BigInteger(std::string value) {
    if (value.empty()) {
        isNegative = false;
        return;
    }

    if (value[0] == '-') {
        this->isNegative = true;
        value = value.substr(1);
    }
    else {
        isNegative = false;
    }

    digits.resize(value.size());
    for (int i = value.size() - 1; i >= 0; i--) {
        if (value[i] < '0' || value[i] > '9') {
			throw std::runtime_error("Invalid input");
		}
        digits[value.size() - 1 - i] = value[i] - '0';
    }
    return;
}

BigInteger::BigInteger(const char* value)
{
    if (strlen(value) == 0) {
        this->digits.clear();
        this->isNegative = false;
        return;
    }

    this->isNegative = value[0] == '-';
    for (int i = 0; value[i]; i++) {
		if (value[i] >= '0' && value[i] <= '9') {
			this->digits.push_back(value[i] - '0');
		}
		else throw std::runtime_error("Invalid input");
    }
	std::reverse(this->digits.begin(), this->digits.end());
    return;
}

// copy constructor
BigInteger::BigInteger(const BigInteger& other) {
    digits = other.digits;
    isNegative = other.isNegative;
    return;
}

// assignment operator
BigInteger& BigInteger::operator=(const BigInteger& other) {
    digits = other.digits;
    isNegative = other.isNegative;
    return *this;
}


// comparison operator
bool BigInteger::operator==(const BigInteger& other) const {
    if (isNegative != other.isNegative) {
        return false;
    }
    if (digits.size() != other.digits.size()) {
        return false;
    }
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    return true;
}

// comparison operator
bool BigInteger::operator!=(const BigInteger& other) const {
    return !(*this == other);
}

// comparison operator
bool BigInteger::operator<(const BigInteger& other) const {
    if (isNegative && !other.isNegative) {
        return true;
    }
    if (!isNegative && other.isNegative) {
        return false;
    }
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    for (int i = digits.size() - 1; i >= 0; i--) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false;
}

// comparison operator
bool BigInteger::operator>(const BigInteger& other) const {
    return !(*this < other || *this == other);
}

// comparison operator
bool BigInteger::operator<=(const BigInteger& other) const {
    return *this < other || *this == other;
}

// comparison operator
bool BigInteger::operator>=(const BigInteger& other) const {
    return *this > other || *this == other;
}


// addition operator
BigInteger BigInteger::operator+(const BigInteger& other) const {
    BigInteger result;
    int carry = 0;
    int i = 0;
    while (i < digits.size() || i < other.digits.size() || carry) {
        if (i < digits.size()) {
            carry += digits[i];
        }
        if (i < other.digits.size()) {
            carry += other.digits[i];
        }
        result.digits.push_back(carry % 10);
        carry /= 10;
        i++;
    }

    if (isNegative && other.isNegative) {
        result.isNegative = true;
    }
    else if (isNegative) {
        if (this->abs() > other) {
            result.isNegative = true;
        }
    }
    else if (other.isNegative) {
        if (*this < other.abs()) {
            result.isNegative = true;
        }
    }
    return result;
}

BigInteger BigInteger::abs() const {
    BigInteger result = *this;
    result.isNegative = false;
    return result;
}

// subtraction operator
BigInteger BigInteger::operator-(const BigInteger& other) const {
    if (isNegative != other.isNegative) {
        return *this + (-other);
    }

    if (abs() < other.abs()) {
        return -(other - *this);
    }

    BigInteger result;
    int borrow = 0;
    for (int i = 0; i < digits.size(); ++i) {
        int diff = digits[i] - borrow;
        if (i < other.digits.size()) {
            diff -= other.digits[i];
        }
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result.digits.push_back(diff);
    }

    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

    result.isNegative = isNegative;
    return result;
}

// multiplication operator
BigInteger BigInteger::operator*(const BigInteger& other) const {
    BigInteger result;
    result.digits.resize(digits.size() + other.digits.size());
    for (int i = 0; i < digits.size(); i++) {
        for (int j = 0; j < other.digits.size(); j++) {
            result.digits[i + j] += digits[i] * other.digits[j];
            result.digits[i + j + 1] += result.digits[i + j] / 10;
            result.digits[i + j] %= 10;
        }
    }

    if (isNegative != other.isNegative) {
        result.isNegative = true;
    }
    return result;
}

// division operator
BigInteger BigInteger::operator/(const BigInteger& other) const {
    BigInteger result;
    if (other == BigInteger(0)) {
        throw std::runtime_error("Division by zero");
    }

    if (*this < other) {
        return BigInteger(0);
    }

    BigInteger current = this->abs();
    BigInteger divisor = other.abs();
    result.digits.resize(digits.size() - other.digits.size() + 1);
    for (int i = digits.size() - other.digits.size(); i >= 0; i--) {
        BigInteger temp = divisor;
        temp.digits.insert(temp.digits.begin(), i, 0);
        while (current >= temp) {
            current = current - temp;
            result.digits[i]++;
        }
    }

    if (isNegative != other.isNegative) {
        result.isNegative = true;
    }
    return result;
}

// modulo operator
BigInteger BigInteger::operator%(const BigInteger& other) const {
    if (other == BigInteger(0)) {
        throw std::runtime_error("Division by zero");
    }

    if (*this < other) {
        return *this;
    }

    BigInteger current = *this;
    BigInteger divisor = other.abs();
    for (int i = digits.size() - other.digits.size(); i >= 0; i--) {
        BigInteger temp = divisor;
        temp.digits.insert(temp.digits.begin(), i, 0);
        while (current >= temp) {
            current = current - temp;
        }
    }

    if (isNegative) {
        current.isNegative = true;
    }
    return current;
}

// unary minus operator
BigInteger BigInteger::operator-() const {
    BigInteger result = *this;
    result.isNegative = !result.isNegative;
    return result;
}

// addition assignment operator
BigInteger& BigInteger::operator+=(const BigInteger& other) {
    *this = *this + other;
    return *this;
}

// subtraction assignment operator
BigInteger& BigInteger::operator-=(const BigInteger& other) {
    *this = *this - other;
    return *this;
}

// multiplication assignment operator
BigInteger& BigInteger::operator*=(const BigInteger& other) {
    *this = *this * other;
    return *this;
}

// division assignment operator
BigInteger& BigInteger::operator/=(const BigInteger& other) {
    *this = *this / other;
    return *this;
}

// modulo assignment operator
BigInteger& BigInteger::operator%=(const BigInteger& other) {
    *this = *this % other;
    return *this;
}

// prefix increment operator
BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

// postfix increment operator
BigInteger BigInteger::operator++(int) {
    BigInteger result = *this;
    *this += 1;
    return result;
}

// prefix decrement operator
BigInteger& BigInteger::operator--() {
    *this -= BigInteger(1);
    return *this;
}

// postfix decrement operator
BigInteger BigInteger::operator--(int) {
    BigInteger result = *this;
    *this -= BigInteger(1);
    return result;
}

// convert to string
std::string BigInteger::toString() const {
    std::string result;
    if (isNegative) {
        result.push_back('-');
    }
    for (int i = digits.size() - 1; i >= 0; i--) {
        result.push_back(digits[i] + '0');
    }
    return result;
}

// convert to integer
int BigInteger::toInt() const {
    int result = 0;
    for (int i = digits.size() - 1; i >= 0; i--) {
        result = result * 10 + digits[i];
    }
    return isNegative ? -result : result;
}

// check if the number is negative
bool BigInteger::getIsNegative() const {
    return this->isNegative;
}

// set the number to negative
void BigInteger::setNegative(bool isNegative) {
    this->isNegative = isNegative;
    return;
}

std::istream& operator>>(std::istream& is, BigInteger& bigInteger) {
    std::string value;
    is >> value;
    bigInteger = BigInteger(value);
    return is;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bigInteger) {
    std::string data = bigInteger.toString();
    if (bigInteger.getIsNegative()) {
        os << "-";
        data.erase(data.begin());
    }
    while (data.size() > 1 && data[0] == '0') {
        data.erase(data.begin());
    }
    os << data;
    return os;
}

BigInteger max(const BigInteger& a, const BigInteger& b)
{
    return a > b ? a : b;
}

BigInteger min(const BigInteger& a, const BigInteger& b)
{
    return a < b ? a : b;
}

BigInteger abs(const BigInteger& a)
{
    return a.abs();
}

BigInteger pow(const BigInteger& base, const BigInteger& exponent)
{
    if (exponent < 0) {
        throw std::runtime_error("Negative exponent");
    }
    BigInteger result = 1;
    for (BigInteger i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

BigInteger sqrt(const BigInteger& a)
{
	if (a < 0) {
		throw std::runtime_error("Negative argument");
	}
	if (a == 0) {
		return 0;
	}
	BigInteger left = 1;
	BigInteger right = a;
	while (left < right) {
		BigInteger mid = (left + right) / 2; 
		if (mid * mid < a) {
			left = mid + 1;
		}   
		else {
			right = mid;
		}
	}
	return left - 1;
}

BigInteger gcd(const BigInteger& a, const BigInteger& b)
{
	return b == 0 ? a : gcd(b, a % b);
}

BigInteger lcm(const BigInteger& a, const BigInteger& b)
{
	return a / gcd(a, b) * b;
}

BigInteger factorial(const BigInteger& a)
{
	if (a < 0) {
		throw std::runtime_error("Negative argument");
	}
	BigInteger result = 1;
	for (BigInteger i = 1; i <= a; i++) {
		result *= i;
	}
	return result;
}

BigInteger modPow(const BigInteger& base, const BigInteger& exponent, const BigInteger& mod)
{
	if (exponent < 0) {
		throw std::runtime_error("Negative exponent");
	}
	BigInteger result = 1;
	BigInteger basePower = base % mod;
	for (BigInteger i = 0; i < exponent; i++) {
		result = (result * basePower) % mod;
	}
	return result;
}


BigInteger BigInteger::operator^(const BigInteger& other)
{
	if (other == 0) {
		return BigInteger(1);
	}

	if (other < 0) {
		throw std::runtime_error("Negative exponent");
	}
    
	BigInteger result = 1;
	for (BigInteger i = 0; i < other; i++) {
		result *= *this;
	}
	return result;
}

