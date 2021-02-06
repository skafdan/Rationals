#include "Integer.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
#define BASE 10

namespace cosc326 {

	Integer::Integer() 
	: sign(true),
	  digits(1,0),
	  numDigits(1)
	{
        //Initialzation handled by initializer list.
	}

	Integer::Integer(const Integer& i) {
		// A copy constructor that duplicates the provided Integer.
		this->numDigits = i.numDigits;
		this->digits = i.digits;
		this->sign = i.sign;
	}

	Integer::Integer(const std::string& s)
		: sign(true),
		  numDigits(0),
		  digits(s.length(),'0'){
		/**
		 * One that takes a std::string of digits (possibly with a leading + or
		 * -).
		 */
		 // take int and put in num backwards
        int k;
        int limit = 0;
        if (s.length() == 0){
            digits.resize(1);
            addSigDigit(0);
            return;
        }
        if(s.at(0) == '-'){
            sign = false;
            limit = 1;
        }
        if (s.at(0) == '+'){
            sign = true;
            limit = 1;
        }
        for(k=s.length() - 1; k >= limit; k--){
            if(isdigit(s[k])){
                addSigDigit(s.at(k) - '0');
            }else {
                std::cerr << "malformed int" << std::endl;
                abort();
            }
        }
	}
	
	Integer::~Integer() {
		//destructor 
	}

	Integer& Integer::operator=(const Integer& i) {
		this->sign = i.sign;
		this->digits = i.digits;
		this->numDigits = i.numDigits;
		return *this;
	}

	Integer Integer::operator-() const {
		Integer negativeCopy(*this);
		negativeCopy.sign = false;
		//return Integer(*this);
		return negativeCopy;
	}

	Integer Integer::operator+() const {
		Integer positiveCopy(*this);
		positiveCopy.sign = true;
		//return Integer(*this);
		return positiveCopy;
	}

	Integer& Integer::operator+=(const Integer& i) {
		int sum;
		int carry = 0;
		int length = this->numDigits;
		if(length < i.numDigits){
			length = i.numDigits;
		}
		if (this->sign != i.sign){
			Integer flippedSignI(i);	
			flippedSignI.sign = !flippedSignI.sign;
			*this -= flippedSignI;
			return *this;
		}
		for(int k = 0; k < length; k++){
			sum = this->getDigit(k) + i.getDigit(k) + carry;
			carry = sum/BASE;
			sum = sum % BASE;
			if(k < this->numDigits){
				this->changeDigit(k,sum);
			}else {
				this->addSigDigit(sum);
			}
			
		}
		if(carry != 0){
			this->addSigDigit(carry);
		}
		return *this;
	}

	Integer& Integer::operator-=(const Integer& i) {
		int diff;
		int borrow = 0;

		int length = numDigits;
		if (*this == i){
			Integer zero;
			*this = zero;
			return *this;
		}

		if(this->sign != i.sign){
			Integer flippedSignI(i);
			flippedSignI.sign = !flippedSignI.sign;
			*this += flippedSignI;
			return *this;
		}
		//Assuming signs are the same. Take larger and place on top.
		if (this->sign && (*this) < i || 
			!(this->sign) && (*this) > i){
			*this = i - *this;
			if (this->sign){
				this->sign = !this->sign;
			} else {
				this->sign = !this->sign;
			}
			return *this;	
		}
		for(int k = 0; k < length; k++){
			diff = getDigit(k) - i.getDigit(k) - borrow;
			borrow = 0;
			if ( diff < 0){
				diff += 10;
				borrow = 1;
			}
			changeDigit(k,diff);
		}
		normalize();
		return *this;
	}

	Integer& Integer::operator*=(const Integer& i) {
		if(this->sign != i.sign){
            this->sign = false;
		}else {
            this->sign = true;
        }
        Integer copy(*this);
        Integer sum("0");
        Integer ten("10");
        int length = i.numDigits;
        for(int k = 0; k < length; k++){
            sum += primTimesInt(copy,i.getDigit(k));
            copy = primTimesInt(copy,10);
        }
        *this = sum;
		return *this;
    }
    Integer Integer::primTimesInt(Integer& i, int x){
        int carry = 0;
        int product;
        int length = i.numDigits;
        Integer zero("0");
        Integer result = i;
        if(0 == x){
            result = zero;
            return result;
        }
        for(int k = 0; k < length; k++){
            product = x * result.getDigit(k) + carry;
            carry = product / BASE;
            result.changeDigit(k,product % BASE);
        }
        while(carry != 0){
            result.addSigDigit(carry % BASE);
            carry /= BASE;
        }
        return result;
    }
	Integer& Integer::operator/=(const Integer& i) {
		return *this;
	}

	Integer& Integer::operator%=(const Integer& i) {
		return *this;
	}

	Integer operator+(const Integer& lhs, const Integer& rhs) {
		Integer sum(lhs);
		sum += rhs;
		return sum;
	}

	Integer operator-(const Integer& lhs, const Integer& rhs) {
		Integer sum(lhs);
		sum -= rhs;
		return sum;
	}

	Integer operator*(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}

	Integer operator/(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}

	Integer operator%(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}


	std::ostream& operator<<(std::ostream& os, const Integer& i) {
		os << i.toString();
		return os;
	}

	std::istream& operator>>(std::istream& is, Integer& i) {
		std::string s;
		is >> s;
		i = Integer(s);
		return is;
	}

	bool operator<(const Integer& lhs, const Integer& rhs) {
		//-rhs && +lhs rhs cant not be greater than lhs.
        if(rhs == lhs){
            return false;
        }else if(rhs.sign == false && lhs.sign == true){
			return false;
		//Same sign(+) but length of rhs < length of lhs, lhs cant be greater.
		}else if ((rhs.sign == true && lhs.sign == true)
			&& lhs.getNumDigits() > rhs.getNumDigits()){ 
			return false;
        //Same sign(-) but length of rhs > length of lhs, rhs cant be greater.
        }else if ((rhs.sign == false && lhs.sign == false) 
            && lhs.getNumDigits() < rhs.getNumDigits()){
                return false;
		}else if(rhs.sign == lhs.sign && //If a digit is greater on the lhs.
			rhs.getNumDigits() == lhs.getNumDigits()){
            int k = rhs.getNumDigits()-1;
            while(k >= 0){
                if(lhs.getDigit(k) > rhs.getDigit(k)){
                    return false;
                }
				k--;
            }
		}
		return true;
	}

	bool operator> (const Integer& lhs, const Integer& rhs) {
        if(lhs == rhs){
            return false;
        }
		return rhs < lhs;
	}

	bool operator<=(const Integer& lhs, const Integer& rhs) {
        if(lhs < rhs || lhs == rhs){
            return true;
        }
		return false;
	}

	bool operator>=(const Integer& lhs, const Integer& rhs) {
        if((lhs>rhs) || lhs == rhs){
            return true;
        }
		return false;
	}

	bool operator==(const Integer& lhs, const Integer& rhs) {
		return equal(lhs, rhs);
	}

	bool operator!=(const Integer& lhs, const Integer& rhs) {
		return !(lhs==rhs);
	}


	Integer gcd(const Integer& a, const Integer& b) {
		return a;
	}
    int Integer::getDigit(int k) const{
        if(0 <= k && k < this->numDigits){
            return this->digits[k];
        }
        return 0;
    }
    void Integer::addSigDigit(int value){
        if(numDigits >= digits.size()) digits.resize(digits.size() * 2);
        digits[numDigits] = value;
        numDigits++;
    }
    void Integer::changeDigit(int k,int value){
        if(k < 0 || k > numDigits){
            std::cerr << "Cant change digit " << k << ".only " << numDigits << std::endl;
        }else {
            digits[k] = value;
        }
    }
	int Integer::getNumDigits() const{
		return this->numDigits;
	}
    std::string Integer::toString() const{
        std::stringstream ss;
        if(sign == false){
            ss << "-";
        }
        for(int i = numDigits-1; i >= 0; i--){
            ss << digits[i];
        }
        return ss.str();
    }
	void Integer::normalize(){
		//To be implemented
	}
	bool equal(const Integer& lhs, const Integer& rhs){
		if((lhs.sign != rhs.sign) || (lhs.numDigits != rhs.numDigits)){
			return false;
		}else { //At this point the numDigits and sign must be equal
			for(int i = lhs.getNumDigits() - 1; i >= 0; i--){
				if(lhs.getDigit(i) != rhs.getDigit(i)){
					return false;
				}
			}
		}
		return true;
	}
	bool Integer::isNegative(){
		return !this->sign;
	}
	bool Integer::isPositive(){
		return this->sign;
	}
}
