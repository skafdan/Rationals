#include "Rational.h"
#include "Integer.h"
#include <string>
#include <sstream>

namespace cosc326 {

	Rational::Rational() 
    : numerator("0"),
      denominator("0"),
      quotient("0"),
      remain("0")
	{
        //Initialzation handled by initializer list.
	}

	Rational::Rational(const std::string& str) 
    {
        std::stringstream ss(str);
        std::string numStr;
        std::string denomStr;
        std::getline(ss,numStr, '/');
        std::getline(ss,denomStr, '/');
        denominator = Integer(denomStr);
        numerator = Integer(numStr);
        quotient = numerator/denominator;
        remain = numerator % denominator;
	}

	Rational::Rational(const Rational& r) {
        this->denominator = r.denominator;
        this->numerator = r.numerator;
        this->quotient = r.quotient;
        this->remain = r.remain;
	}

	Rational::Rational(const Integer& a) 
    {
        Integer one("1");
        numerator = a;
        denominator = one;
		quotient = numerator / denominator;
		remain = numerator % denominator;
	}

	Rational::Rational(const Integer& a, const Integer& b) {
        numerator = a;
        denominator = b;
		quotient = numerator/denominator;
		remain = numerator % denominator;
	}

	Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
        numerator = a + b;
        denominator = c;
		quotient = numerator / denominator;
		remain = numerator % denominator;
	}

	Rational::~Rational() {

	}

	Rational& Rational::operator=(const Rational& r) {
		this->numerator = r.numerator;
		this->denominator = r.denominator;
		this->quotient = r.quotient;
		this->remain = r.remain;
		return *this;
	}

	Rational Rational::operator-() const {
		Rational negativeCopy(*this);
		Integer negativeOne("-1");
        if(negativeCopy.denominator.getSign() == true && 
            negativeCopy.numerator.getSign() == true){
            negativeCopy.numerator *= negativeOne;
        }else if (negativeCopy.denominator.getSign() !=
            negativeCopy.numerator.getSign()){
                if(negativeCopy.numerator.getSign() == false){
                    negativeCopy.numerator *= negativeOne;
                }
                if(negativeCopy.denominator.getSign() == false){
                    negativeCopy.denominator *= negativeOne;
                }
        }else if(negativeCopy.denominator.getSign() == false && 
            negativeCopy.numerator.getSign() == false){
                negativeCopy.numerator *= negativeOne;
        }
        return negativeCopy;
	}

	Rational Rational::operator+() const {
		Rational positiveCopy(*this);
		Integer negativeOne("-1");
        if(positiveCopy.denominator.getSign() == false &&
            positiveCopy.numerator.getSign() == false){
                return positiveCopy;
        }else if (positiveCopy.denominator.getSign() != 
            positiveCopy.numerator.getSign()){
                if(positiveCopy.numerator.getSign() == false){
                     positiveCopy.numerator *= negativeOne;
                }
                if(positiveCopy.denominator.getSign() == false){
                    positiveCopy.denominator *= negativeOne;
                }
        }
		return positiveCopy;
	}

	Rational& Rational::operator+=(const Rational& r) {
		if(this->getDenominator() == r.getDenominator()){
			this->numerator += r.numerator;
		}else {
			this->numerator = (this->numerator * r.denominator) + (r.numerator * this->denominator);
			this->denominator *= r.denominator;
		}
        *this = updateQR();
		return *this;
	}


	Rational& Rational::operator-=(const Rational& r) {
		*this = *this + -r;
        *this = updateQR();
		return *this;
	}

	Rational& Rational::operator*=(const Rational& r) {
		this->numerator *= r.numerator;
		this->denominator *= r.denominator;
        *this = updateQR();
		return *this;
	}

	Rational& Rational::operator/=(const Rational& r) {
		Rational flipped(r);
		flipped.numerator = r.denominator;
		flipped.denominator = r.numerator;
		*this *= flipped;
        *this = updateQR();
		return *this;
	}

	Rational operator+(const Rational& lhs, const Rational& rhs) {
		Rational result(lhs);
		result += rhs;
		return result;
	}

	Rational operator-(const Rational& lhs, const Rational& rhs) {
		Rational result(lhs);
		result += rhs;
		return result;
	}

	Rational operator*(const Rational& lhs, const Rational& rhs) {
		Rational result(lhs);
		result *= rhs;
		return rhs;
	}

	Rational operator/(const Rational& lhs, const Rational& rhs) {
		Rational result(lhs);
		result /= rhs;
		return result;
	}

	std::ostream& operator<<(std::ostream& os, const Rational& i) {
		os << i.getNumerator() << "/" << i.getDenominator(); 
		return os;
	}
	std::istream& operator>>(std::istream& is, Rational& i) {
		std::string s;
		is >> s;
		i = Rational(s);
		return is;
	}

	bool operator<(const Rational& lhs, const Rational& rhs) {
        if(lhs == rhs){
            return false;
        }else if(lhs.getQuotient() > rhs.getQuotient()){
            return false;
        }else if(lhs.getQuotient() == rhs.getQuotient() && 
            lhs.getRemainder() > rhs.getRemainder()){
            return false;
        }
		return true;
	}

	bool operator> (const Rational& lhs, const Rational& rhs) {
        if(lhs == rhs){
            return false;
        }
		return rhs < lhs;
	}

	bool operator<=(const Rational& lhs, const Rational& rhs) {
        if((lhs <= rhs) || lhs == rhs){
            return true;
        }
		return false;
	}

	bool operator>=(const Rational& lhs, const Rational& rhs) {
       if((lhs >= rhs) || lhs == rhs){
           return true;
       } 
		return false;
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		if(lhs.getQuotient() != rhs.getQuotient()){
			return false;
		}else if (lhs.getRemainder() != rhs.getRemainder()){
			return false;
		}
		return true;
	}

	bool operator!=(const Rational& lhs, const Rational& rhs) {
        if(lhs.getQuotient() == rhs.getQuotient()){
            if(lhs.getRemainder() == rhs.getRemainder()){
                return false;
            }
        }
		return true;
	}
	Integer Rational::getNumerator() const{
		return this->numerator;
	}
	Integer Rational::getDenominator() const{
		return this->denominator;
	}
	Integer Rational::getQuotient() const{
		return this->quotient;
	}
	Integer Rational::getRemainder() const{
		return this->remain;
	}
    Rational Rational::updateQR() const{
        Rational updated(*this);
        updated.quotient = updated.numerator / updated.denominator;
        updated.remain = updated.numerator % updated.denominator;
        return updated;
    }
}
