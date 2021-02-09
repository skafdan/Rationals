/**
 * Cosc326 Rational class header file.
 * @author Dan Skaf, Elijah Passmore
 * 09/02/2021
 * */
#pragma once

// Most compilers understand the once pragma, but just in case...
#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include "Integer.h"
#include <iostream>
#include <string>

namespace cosc326
{

class Rational
{

  public:
    /**
     * Initializes Rational to 0.
     * */
    Rational();
    /**
     * Creates Rational from string
     * @param str to create Rational.
     * */
    Rational(const std::string &str);
    /**
     * Copies Rational from another Instance
     * @param r Rational to copy
     * */
    Rational(const Rational &r);
    /**
     * Create Rational from Integer.
     * @param a Integer.
     * */
    Rational(const Integer &a);                                     // a
    /**
     * Create Rational from two Integers.
     * @param a Integer.
     * @param b Integer.
     * */
    Rational(const Integer &a, const Integer &b);                   // a/b
    /**
     * Create Rational from sum of two integers and a 3rd.
     * */
    Rational(const Integer &a, const Integer &b, const Integer &c); // a + b/c

    ~Rational();
    /**
     * Assignment operator
     * @param r Rational to be assigned.
     * */
    Rational &operator=(const Rational &r); // q = r;

    // Unary operators
    Rational operator-() const; // -r;
    Rational operator+() const; // +r;

    // Arithmetic assignment operators
    Rational &operator+=(const Rational &r); // q += r;
    Rational &operator-=(const Rational &r); // q -= r;
    Rational &operator*=(const Rational &r); // q *= r;
    Rational &operator/=(const Rational &r); // q /= r;

    // lhs < rhs -- a 'friend' means < isn't a member, but can access the private
    // parts of the class. You may need to make some other functions friends, but
    // do so sparingly.
    friend bool operator<(const Rational &lhs, const Rational &rhs);
    /**
     * Gets numerator Integer.
     * */
    Integer getNumerator() const;
    /**
     * Gets denominator Integer.
     * */
    Integer getDenominator() const;
    /**
     * Gets quotient Integer.
     * */
    Integer getQuotient() const;
    /**
     * Gets remainder Integer.
     * */
    Integer getRemainder() const;
    /**
     * Simplifies the Rational by calculating GCD of numerator and denominator 
     * and dividing both by GCD.
     * @param i Rational to simplify
     * @return Rational.
     * */
    Rational simplify(Rational i) const;

  private:
    // Can add internal storage or methods here
    Integer numerator;
    Integer denominator;
    Integer quotient;
    Integer remain;
    /**
     * Recalculates quotient and remainder.
     * */
    Rational updateQR() const;
};

// Binary operators
Rational operator+(const Rational &lhs, const Rational &rhs); // lhs + rhs;
Rational operator-(const Rational &lhs, const Rational &rhs); // lhs - rhs;
Rational operator*(const Rational &lhs, const Rational &rhs); // lhs * rhs;
Rational operator/(const Rational &lhs, const Rational &rhs); // lhs / rhs;

std::ostream &operator<<(std::ostream &os,
                         const Rational &i);             // std::cout << i << std::endl;
std::istream &operator>>(std::istream &is, Rational &i); // std::cin >> i;

bool operator>(const Rational &lhs, const Rational &rhs);  // lhs > rhs
bool operator<=(const Rational &lhs, const Rational &rhs); // lhs <= rhs
bool operator>=(const Rational &lhs, const Rational &rhs); // lhs >= rhs
bool operator==(const Rational &lhs, const Rational &rhs); // lhs == rhs
bool operator!=(const Rational &lhs, const Rational &rhs); // lhs != rhs

} // namespace cosc326

#endif
