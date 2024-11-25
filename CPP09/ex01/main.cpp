// main.cpp
#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv) 
{
    if (argc != 2) {
        std::cout << "Error" << std::endl;
        return 1;
    }
    
    RPN calculator;
    try {
        int result = calculator.calculate(argv[1]);
        std::cout << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}