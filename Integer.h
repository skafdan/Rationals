/**
 * Cosc326 Large Integer class header file.
 * @author Dan Skaf, Elijah Passmore
 * 09/02/2021
 * */
// Most compilers understand the once pragma, but just in case...
#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

namespace cosc326
{

class Integer
{

  public:
    /**
     * Default constructer. Initializes Integer to 0.
     * */
    Integer();                     // Integer i;
    /**
     * Creates Integer from passed Integer.
     * @param i const Integer. Passed Integer.
     * */
    Integer(const Integer &i);     // Integer j(i);
    /**
     * Creates Integer from string.
     * @param s std::string. Passed string.
     * */
    Integer(const std::string &s); // Integer k("123");

    ~Integer();//Destructer 
    /**
     * = operator. Assignment operator
     * */ 
    Integer &operator=(const Integer &i); // j = i;

    // Unary operators
    Integer operator-() const; // -j;
    Integer operator+() const; // +j;

    // Arithmetic assignment operators
    Integer &operator+=(const Integer &i); // j += i;
    Integer &operator-=(const Integer &i); // j -= i;
    Integer &operator*=(const Integer &i); // j *= i;
    Integer &operator/=(const Integer &i); // j /= i;
    Integer &operator%=(const Integer &i); // j %= i;
    // lhs < rhs -- a 'friend' means operator isn't a member, but can access the
    // private parts of the class. You may need to make some other functions
    // friends, but do so sparingly.
    friend bool operator<(const Integer &lhs, const Integer &rhs);
    /**
     * Helper function that checks that two Integers are equal.
     * @param lhs, left hand side Integer.
     * @param rhs, right hand side Integer.
     * @return Boolean true if lhs = rhs, false otherwise.
     * */
    friend bool equal(const Integer &lhs, const Integer &rhs);

    /**
     * Accessor for numdigits data field.
     * */
    int getNumDigits() const;
    /**
     * toString for Integer class.
     * @return String form of Integer.
     * */
    std::string toString() const;
    /**
     * Accessor for sign;
     * @return Boolean true if negative.
     * */
    bool isNegative();
    /**
     * Accessor for sign;
     * @return Boolean true if positive.
     * */
    bool isPositive();
    /**
     * Accessor for sign
     * @return Boolean sign.
     * */
    bool getSign();

  private:
    // Data fields
    bool sign;
    std::vector<int> digits;
    int numDigits;
    // methods
    /**
     * Returns a digit at the index k.
     * @param k index to return digit.
     * @return int at index k.
     * */
    int getDigit(int k) const;
    /**
     * Adds a significant digit to vector<int> digits off passed value.
     * Adjusting space of vector if required.
     * @param value int to add.
     * */ 
    void addSigDigit(int value);
    /**
     * changes digit of index k, if k out of range throws exception if k 
     * out of bounds.
     * @param k int index.
     * @param value int to add.
     * */
    void changeDigit(int k, int value);
    /**
     * Removes leading zeros.
     * */
    void normalize();
    /**
     * Multiples the Integer by a primitive type int. Only used in *= operator.
     * @param i Integer& lhs.
     * @param x int rhs.
     * @return Integer multipled by int.
     * */
    Integer primTimesInt(Integer &i, int x);
};
// Binary operators
Integer operator+(const Integer &lhs, const Integer &rhs); // lhs + rhs;
Integer operator-(const Integer &lhs, const Integer &rhs); // lhs - rhs;
Integer operator*(const Integer &lhs, const Integer &rhs); // lhs * rhs;
Integer operator/(const Integer &lhs, const Integer &rhs); // lhs / rhs;
Integer operator%(const Integer &lhs, const Integer &rhs); // lhs % rhs;

std::ostream &operator<<(std::ostream &os, const Integer &i);// std::cout << i << std::endl;
std::istream &operator>>(std::istream &is, Integer &i); // std::cin >> i;

bool operator>(const Integer &lhs, const Integer &rhs);  // lhs > rhs
bool operator<=(const Integer &lhs, const Integer &rhs); // lhs <= rhs
bool operator>=(const Integer &lhs, const Integer &rhs); // lhs >= rhs
bool operator==(const Integer &lhs, const Integer &rhs); // lhs == rhs
bool operator!=(const Integer &lhs, const Integer &rhs); // lhs != rhs

Integer gcd(const Integer &a, const Integer &b); // i = gcd(a, b);

} // namespace cosc326

#endif
