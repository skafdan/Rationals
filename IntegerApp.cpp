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
    std::string input2;
    getline(std::cin,input1);
    getline(std::cin,input2);
    cosc326::Integer x(input1);
    cosc326::Integer y(input2);
    std::cout << (x < y) << std::endl;
    return 0;
}
