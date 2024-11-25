#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>

class PmergeMe 
{
private:
    std::vector<int> vector;
    std::deque<int> deque;

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    template <typename T>
    void print(T& container);

    bool isValidNumber(const std::string& str);
    bool sort(char** av); 

    template <typename T>
    void fordJohnson(T& container);

    template <typename T>
    void insertion(T& container);
};

#endif
