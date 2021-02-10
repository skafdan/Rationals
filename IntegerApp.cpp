#include <iostream>

#include "Integer.h"
#include "Rational.h"

int main()
{
    cosc326::Rational myrat(cosc326::Integer("15"),cosc326::Integer("32"),cosc326::Integer("2"));
    //std::cout<<"The greatest common divisorof,\n\t"<<a<<"\n\t"<<b<<"\nis,\n\t";
    //std::cout<<cosc326::gcd(a,b)<<"\n";
    std::string rationalStr = "2452345345234123123178/23459023850983290589042";
    //cosc326::Integer x(a);
    //cosc326::Integer y(b);
    //std::cout << x % y << "\n";
    std::cout << cosc326::Rational(myrat) << "\n";
    return 0;
}
