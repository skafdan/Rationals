/**
 * Cosc326 Large Integer Class
 * @author Dan Skaf, Elijah Passmore.
 * 9/02/2021
 * */
#include "Integer.h"

#include <math.h>

#include <algorithm>
#include <sstream>
#include <vector>
#define BASE 10

namespace cosc326
{
/* Constructors */
Integer::Integer() : sign(true), digits(1, 0), numDigits(1)
{
    // Initialzation handled by initializer list.
}

Integer::Integer(const Integer &i)
{
    this->numDigits = i.numDigits;
    this->digits = i.digits;
    this->sign = i.sign;
}

Integer::Integer(const std::string &s) 
: sign(true),
  numDigits(0),
  digits(s.length(), '0')
{
    int k;
    int limit = 0;
    if (s.length() == 0)
    {
        digits.resize(1);
        addSigDigit(0);
        return;
    }
    if (s.at(0) == '-')
    {
        sign = false;
        limit = 1;
    }
    if (s.at(0) == '+')
    {
        sign = true;
        limit = 1;
    }
    for (k = s.length() - 1; k >= limit; k--)
    {
        if (isdigit(s[k]))
        {
            addSigDigit(s.at(k) - '0');
        }
        else
        {
            throw "Malformed int";
        }
    }
    normalize();
}

Integer::~Integer()
{
    // destructor
}

Integer &Integer::operator=(const Integer &i)
{
    this->sign = i.sign;
    this->digits = i.digits;
    this->numDigits = i.numDigits;
    return *this;
}

Integer Integer::operator-() const
{
    Integer negativeCopy(*this);
    Integer negativeOne("-1");
    negativeCopy *= negativeOne;
    return negativeCopy;
}

Integer Integer::operator+() const
{
    Integer positiveCopy(*this);
    positiveCopy.sign = true;
    // return Integer(*this);
    return positiveCopy;
}

Integer &Integer::operator+=(const Integer &i)
{
    int sum;
    int carry = 0;
    int length = this->numDigits;
    if (length < i.numDigits)
    {
        length = i.numDigits;
    }
    if (this->sign != i.sign)//Treat negative addition as subtraction.
    {
        Integer flippedSignI(i);
        flippedSignI.sign = !flippedSignI.sign;
        *this -= flippedSignI;
        return *this;
    }
    for (int k = 0; k < length; k++)
    {
        sum = this->getDigit(k) + i.getDigit(k) + carry;
        carry = sum / BASE;
        sum = sum % BASE;
        if (k < this->numDigits)
        {
            this->changeDigit(k, sum);
        }
        else
        {
            this->addSigDigit(sum);
        }
    }
    if (carry != 0)
    {
        this->addSigDigit(carry);
    }
    return *this;
}

Integer &Integer::operator-=(const Integer &i)
{
    int diff;
    int borrow = 0;
    Integer rhs(i);
    int length = numDigits;
    if (*this == i)
    {
        Integer zero;
        *this = zero;
        return *this;
    }

    if (this->isNegative() != rhs.isNegative())
    {
        Integer flippedSignI(rhs);
        flippedSignI.sign = !flippedSignI.sign;
        *this += flippedSignI;
        return *this;
    }
    // Assuming signs are the same. Take larger and place on top.
    if (this->isPositive() && (*this) < rhs 
        || this->isNegative() && (*this) > rhs)
    {
        *this = rhs - *this;
        if (this->isPositive())
        {
            this->sign = false;
        }
        else
        {
            this->sign = true;
        }
        return *this;
    }
    for (int k = 0; k < length; k++)
    {
        diff = getDigit(k) - rhs.getDigit(k) - borrow;
        borrow = 0;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        changeDigit(k, diff);
    }
    normalize();
    return *this;
}

Integer &Integer::operator*=(const Integer &i)
{
    if (this->sign != i.sign)// -x * +y = - z
    {
        this->sign = false;
    }
    else //-x * -y = +z
    {
        this->sign = true;
    }
    Integer copy(*this);
    Integer sum("0");
    Integer ten("10");
    int length = i.numDigits;
    for (int k = 0; k < length; k++)
    {
        sum += primTimesInt(copy, i.getDigit(k));
        copy = primTimesInt(copy, 10);
    }
    *this = sum;
    return *this;
}

Integer &Integer::operator/=(const Integer &i)
{
    Integer quotient("0");
    Integer dividend(*this);
    Integer divisor(i);
    Integer zero("0");
    if (i == zero)
    {
        throw "Division by zero";
    }
    if (this->isNegative() && divisor.isNegative())//-x/-y = +z
    {
        Integer lhsPositive(+*this);
        Integer rhsPositive(+divisor);
        lhsPositive /= rhsPositive;
        *this = lhsPositive;
        return *this;
    }
    if (divisor < zero) //+x / - y = +x / +y =  -1 * (+z)
    {
        quotient = dividend / +divisor;
        quotient.sign = false;
        *this = quotient;
        return *this;
    }
    if (dividend < zero) //Same as above condition 
    {
        quotient = +dividend / divisor;
        quotient.sign = false;
        *this = quotient;
        return *this;
    }
    std::string result;
    std::string number = toString();
    long primDivisor;
    std::stringstream ss(i.toString());
    ss >> primDivisor;
    int idx = 0;
    long temp = number[idx] - '0';
    while (temp < primDivisor)
        temp = temp * 10 + (number[++idx] - '0');
    while (number.size() > idx)
    {
        result += (temp / primDivisor) + '0';
        temp = (temp % primDivisor) * 10 + number[++idx] - '0';
    }
    if (result.length() == 0)
    {
        result = "0";
    }
    *this = Integer(result);
    return *this;
}

Integer &Integer::operator%=(const Integer &i)
{
    int result = 0;
    long primDivisor;
    std::stringstream ss(i.toString());
    ss >> primDivisor;
    std::string number = toString();
    for (int i = 0; i < number.length(); i++)
    {
        result = (result * 10 + (int)number[i] - '0') % primDivisor;
    }
    *this = Integer(std::to_string(result));
    return *this;
}

Integer operator+(const Integer &lhs, const Integer &rhs)
{
    Integer sum(lhs);
    sum += rhs;
    return sum;
}

Integer operator-(const Integer &lhs, const Integer &rhs)
{
    Integer result(lhs);
    result -= rhs;
    return result;
}

Integer operator*(const Integer &lhs, const Integer &rhs)
{
    Integer result = lhs;
    result *= rhs;
    return result;
}

Integer operator/(const Integer &lhs, const Integer &rhs)
{
    Integer result = lhs;
    result /= rhs;
    return result;
}

Integer operator%(const Integer &lhs, const Integer &rhs)
{
    Integer result(lhs);
    result %= rhs;
    return result;
}

std::ostream &operator<<(std::ostream &os, const Integer &i)
{
    os << i.toString();
    return os;
}

std::istream &operator>>(std::istream &is, Integer &i)
{
    std::string s;
    is >> s;
    i = Integer(s);
    return is;
}

bool operator<(const Integer &lhs, const Integer &rhs)
{
    Integer lhsCopy(lhs);
    Integer rhsCopy(rhs);
    if (lhsCopy.isNegative() != rhsCopy.isNegative())
    {
        return lhsCopy.isNegative();
    }
    if (lhsCopy.numDigits != rhsCopy.numDigits)
    {
        return (lhsCopy.numDigits < rhsCopy.numDigits && lhsCopy.isPositive()) ||
               (lhsCopy.numDigits > rhs.numDigits && lhsCopy.isNegative());
    }

    int length = lhs.numDigits;
    for (int k = length - 1; k >= 0; k--)
    {
        if (lhsCopy.getDigit(k) < rhs.getDigit(k))
            return lhsCopy.isPositive();
        if (lhsCopy.getDigit(k) > rhs.getDigit(k))
            return lhsCopy.isNegative();
    }
    return false;
}

bool operator>(const Integer &lhs, const Integer &rhs)
{
    if (lhs == rhs)
    {
        return false;
    }
    return rhs < lhs;
}

bool operator<=(const Integer &lhs, const Integer &rhs)
{
    if (lhs < rhs || lhs == rhs)
    {
        return true;
    }
    return false;
}

bool operator>=(const Integer &lhs, const Integer &rhs)
{
    if ((lhs > rhs) || lhs == rhs)
    {
        return true;
    }
    return false;
}

bool operator==(const Integer &lhs, const Integer &rhs)
{
    return equal(lhs, rhs);
}

bool operator!=(const Integer &lhs, const Integer &rhs)
{
    return !(lhs == rhs);
}

Integer gcd(const Integer &a, const Integer &b)
{
    Integer remainder(a % b); 
    std::stringstream ss(a.toString());
    long primA;
    ss >> primA;
    std::stringstream ss2(remainder.toString());
    long primReminader;
    ss2 >> primReminader;
    long result = std::__gcd(primA, primReminader);
    return Integer(std::to_string(result));
}
int Integer::getDigit(int k) const
{
    if (0 <= k && k < this->numDigits)
    {
        return this->digits[k];
    }
    return 0;
}
void Integer::addSigDigit(int value)
{
    if (numDigits >= digits.size())
        digits.resize(digits.size() * 2);
    digits[numDigits] = value;
    numDigits++;
}
void Integer::changeDigit(int k, int value)
{
    if (k < 0 || k > numDigits)
    {
        throw "Index out of bounds";
    }
    else
    {
        digits[k] = value;
    }
}
int Integer::getNumDigits() const
{
    return this->numDigits;
}
std::string Integer::toString() const
{
    std::stringstream ss;
    if (sign == false)
    {
        ss << "-";
    }
    for (int i = numDigits - 1; i >= 0; i--)
    {
        ss << digits[i];
    }
    return ss.str();
}
void Integer::normalize()
{
    int i;
    int length = this->numDigits;
    for (i = length - 1; i >= 0; i--)
    {
        if (this->getDigit(i) != 0)
            break;
        this->numDigits--;
    }
    if (i < 0)
    {
        this->numDigits = 1;
        this->sign = true;
    }
}
bool equal(const Integer &lhs, const Integer &rhs)
{
    if ((lhs.sign != rhs.sign) || (lhs.numDigits != rhs.numDigits))
    {
        return false;
    }
    else
    { // At this point the numDigits and sign must be equal
        for (int i = lhs.getNumDigits() - 1; i >= 0; i--)
        {
            if (lhs.getDigit(i) != rhs.getDigit(i))
            {
                return false;
            }
        }
    }
    return true;
}
bool Integer::isNegative()
{
    return !this->sign;
}
bool Integer::isPositive()
{
    return this->sign;
}
bool Integer::getSign()
{
    return this->sign;
}
Integer Integer::primTimesInt(Integer &i, int x)
{
    int carry = 0;
    int product;
    int length = i.numDigits;
    Integer zero("0");
    Integer result = i;
    if (0 == x)
    {
        result = zero;
        return result;
    }
    for (int k = 0; k < length; k++)
    {
        product = x * result.getDigit(k) + carry;
        carry = product / BASE;
        result.changeDigit(k, product % BASE);
    }
    while (carry != 0)
    {
        result.addSigDigit(carry % BASE);
        carry /= BASE;
    }
    return result;
}
} // namespace cosc326
