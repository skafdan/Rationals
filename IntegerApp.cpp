#include <iostream>
#include "Integer.h"

int main(){
    //while(std::cin){
    //    std::string input;
    //    getline(std::cin,input);
    //    cosc326::Integer i(input);
    //    std::cout << i << std::endl;
    //}
    std::string input1;
    getline(std::cin,input1);
    cosc326::Integer x(input1);
    cosc326::Integer y(x);
    cosc326::Integer z;
    z = y;
    std::cout << y << std::endl;
    std::cout << z << std::endl;
    return 0;
}
