#include "PmergeMe.hpp"

int main(int ac, char** av) 
{
    if (ac < 2) 
	{
        std::cerr << "Error: No input provided" << std::endl;
        return 1;
    }
    
    PmergeMe sorter;
    if (!sorter.sort(av)) 
	{
        return 1;
    }
    
    return 0;
}