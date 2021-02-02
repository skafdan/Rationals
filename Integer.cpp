#include "Integer.h"
#include <vector>
#include <sstream>

namespace cosc326 {

	Integer::Integer() {
		// A default constructor that creates Integer with a value of 0.
		std::vector<int> num = {0}
	}

	Integer::Integer(const Integer& i) {
		// A copy constructor that duplicates the provided Integer.
		this->num = i.num;
	}

	Integer::Integer(const std::string& s) {
		/**
		 * One that takes a std::string of digits (possibly with a leading + or
		 * -).
		 */
		 int x = 0;
		 stringstream s2int(s);

		 s2int >> x;
		 // take int and put in num backwards
	}


	Integer::~Integer() {
	
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
		return os;
	}

	std::istream& operator>>(std::istream& is, Integer& i) {
		return is;
	}

	bool operator<(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator> (const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator<=(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator>=(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator==(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator!=(const Integer& lhs, const Integer& rhs) {
		return true;
	}


	Integer gcd(const Integer& a, const Integer& b) {
		return a;
	}

}
