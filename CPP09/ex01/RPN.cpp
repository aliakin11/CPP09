#include "RPN.hpp"
#include <cctype>
#include <cstdlib>


RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other) 
{
    if (this != &other) 
    {
        _stack = other._stack;
    }
    return *this;
}

RPN::~RPN() {}


bool RPN::isOperator(char c) const 
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isNumber(char c) const 
{
    return (c >= '0' && c <= '9');
}

void RPN::performOperation(char op) 
{
    if (_stack.size() < 2)
        throw InvalidExpressionError();
        
    int b = _stack.top();
    _stack.pop();
    int a = _stack.top();
    _stack.pop();
    
    switch (op) 
    {
        case '+':
            _stack.push(a + b);
            break;
        case '-':
            _stack.push(a - b);
            break;
        case '*':
            _stack.push(a * b);
            break;
        case '/':
            if (b == 0)
                throw DivisionByZeroError();
            _stack.push(a / b);
            break;
    }
}


int RPN::calculate(const std::string& expression) 
{
    std::string::const_iterator it;
    for (it = expression.begin(); it != expression.end(); ++it) 
    {
        
        if (*it == ' ')
            continue;
            
        
        if (isNumber(*it)) 
        {
            _stack.push(*it - '0');
            continue;
        }
        
        
        if (isOperator(*it)) 
        {
            performOperation(*it);
            continue;
        }
        
        
        throw InvalidExpressionError();
    }
    
    
    if (_stack.size() != 1)
        throw InvalidExpressionError();
        
    return _stack.top();
}