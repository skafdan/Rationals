#include <iostream>
#include "Integer.h"
#include "Rational.h"

int main(){
    //while(std::cin){
    //    std::string input;
    //    getline(std::cin,input);
    //    cosc326::Integer i(input);
    //    std::cout << i << std::endl;
    //}
    try{
        std::string input1;
        std::string input2;
        getline(std::cin,input1);
        getline(std::cin,input2);
        //cosc326::Rational x(input1);
        cosc326::Integer y(input2);
        cosc326::Integer x(input1);
        //cosc326::Integer y(input2);
        //cosc326::Integer z;
        //std::cout << (x < y) << std::endl;
        //std::cout << (z = gcd(x,y)) << std::endl;
        //std::cout << x % y << std::endl;
        //std::cout << y << std::endl;
        //std::cout << (x += y) << std::endl;
        std::cout << x / y << std::endl;
    }catch (const char* msg){
        std::cerr << msg << std::endl;
    }
    return 0;
}
