#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <stdexcept>

class RPN 
{
private:
    std::stack<int> _stack;
    
    
    bool isOperator(char c) const;
    bool isNumber(char c) const;
    void performOperation(char op);
    
public:
    
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();
    
    
    int calculate(const std::string& expression);
    
    
    class InvalidExpressionError : public std::exception 
    {
        public:
            const char* what() const throw() {
                return "Error";
            }
    };
    
    class DivisionByZeroError : public std::exception 
    {
        public:
            const char* what() const throw() 
            {
                return "Error: Division by zero";
            }
    };
};

#endif