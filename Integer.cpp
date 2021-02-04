#include "Integer.h"
#include <vector>
#include <sstream>

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
		return *this;
	}

	Integer Integer::operator-() const {
		return Integer(*this);
	}

	Integer Integer::operator+() const {
		return Integer(*this);
	}

	Integer& Integer::operator+=(const Integer& i) {
		return *this;
	}

	Integer& Integer::operator-=(const Integer& i) {
		return *this;
	}

	Integer& Integer::operator*=(const Integer& i) {
		return *this;
	}

	Integer& Integer::operator/=(const Integer& i) {
		return *this;
	}

	Integer& Integer::operator%=(const Integer& i) {
		return *this;
	}

	Integer operator+(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}

	Integer operator-(const Integer& lhs, const Integer& rhs) {
		return lhs;
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
		return true;
	}


	Integer gcd(const Integer& a, const Integer& b) {
		return a;
	}
    int Integer::getDigit(int k) const{
        if(k < 0 || k > numDigits){
            return 0;
        }
        return digits[k];
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
			for(int i = lhs.getNumDigits() - 1; i >= 0; i++){
				if(lhs.getDigit(i) != rhs.getDigit(i)){
					return false;
				}
			}
		}
		return true;
	}
}
