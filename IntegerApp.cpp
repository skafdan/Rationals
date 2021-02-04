#include <iostream>
#include "Integer.h"

int main(){
    while(std::cin){
        std::string input;
        getline(std::cin,input);
        cosc326::Integer i(input);
        std::cout << i.toString() << std::endl;
    }
    return 0;
}
