#include "PmergeMe.hpp"
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <climits>
#include <string>


PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : vector(other.vector), deque(other.deque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other) {
        vector = other.vector;
        deque = other.deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}


template <typename T>
void PmergeMe::print(T& container)
{
    for (typename T::iterator it = container.begin(); it != container.end(); ++it) 
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}


bool PmergeMe::isValidNumber(const std::string& str)
{
    if (str.empty()) return false;
    
    size_t i = 0;
    if (str[0] == '+') 
        i++;
    
    if (i == str.length()) return false;
    
    for (; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    
    long number = std::strtol(str.c_str(), NULL, 10);
    if (number < 0 || number > INT_MAX) 
        return false;
    
    return true;
}


bool PmergeMe::sort(char** av)
{
    if (!av[1]) 
    {
        std::cerr << "Error: No input provided" << std::endl;
        return false;
    }

    deque.clear();
    vector.clear();

   
    for (int i = 1; av[i] != NULL; ++i) 
    {
        if (!isValidNumber(av[i])) 
        {
            std::cerr << "Error: Invalid input '" << av[i] << "'" << std::endl;
            return false;
        }
        deque.push_back(std::atoi(av[i]));
    }

    std::cout << "Before: ";
    print(deque);

    
    std::clock_t startTime_deque = std::clock();
    fordJohnson(deque);
    std::clock_t endTime_deque = std::clock();

    std::cout << "After: ";
    print(deque);

    double duration_deque = 10.0 * static_cast<double>(endTime_deque - startTime_deque) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << deque.size() << " elements with std::deque: "
              << std::fixed << std::setprecision(5) << duration_deque << " us" << std::endl;

    
    for (int i = 1; av[i] != NULL; ++i) 
    {
        vector.push_back(std::atoi(av[i]));
    }

    std::clock_t startTime_vector = std::clock();
    fordJohnson(vector);
    std::clock_t endTime_vector = std::clock();

    std::cout << "After: ";
    print(vector);

    double duration_vector = 10.0 * static_cast<double>(endTime_vector - startTime_vector) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << vector.size() << " elements with std::vector: "
              << std::fixed << std::setprecision(5) << duration_vector << " us" << std::endl;

    return (true); 
}


template <typename T>
void PmergeMe::fordJohnson(T& container)
{
    if (container.size() < 2) return;

    size_t mid = container.size() / 2;
    T left(container.begin(), container.begin() + mid);
    T right(container.begin() + mid, container.end());

    insertion(left);
    insertion(right);

    T result;
    typename T::iterator leftIt = left.begin();
    typename T::iterator rightIt = right.begin();

    while (leftIt != left.end() && rightIt != right.end()) 
    {
        if (*leftIt < *rightIt) 
        {
            result.push_back(*leftIt);
            ++leftIt;
        } 
        else 
        {
            result.push_back(*rightIt);
            ++rightIt;
        }
    }

    result.insert(result.end(), leftIt, left.end());
    result.insert(result.end(), rightIt, right.end());

    container = result;
}

template <typename T>
void PmergeMe::insertion(T& container)
{
    for (size_t i = 1; i < container.size(); ++i) 
    {
        typename T::value_type tmp = container[i];
        size_t j = i;
        while (j > 0 && container[j - 1] > tmp) 
        {
            container[j] = container[j - 1];
            --j;
        }
        container[j] = tmp;
    }
}
