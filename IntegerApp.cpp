#include <iostream>

#include "Integer.h"
#include "Rational.h"

int main()
{
    std::string a = "-12";
    std::string b = "-5";
    std::cout<<"The greatest common divisorof,\n\t"<<a<<"\n\t"<<b<<"\nis,\n\t";
    std::cout<<cosc326::gcd(a,b)<<"\n";
    std::string rationalStr = "2452345345234123123178/23459023850983290589042";
    cosc326::Integer x(a);
    cosc326::Integer y(b);
    std::cout << x % y << "\n";
    return 0;
}
