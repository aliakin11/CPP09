#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

class BitcoinExchange 
{
private:
    std::map<std::string, double> _database;
public:
    
    BitcoinExchange();                                     
    BitcoinExchange(const std::string& databaseFile);       
    BitcoinExchange(const BitcoinExchange& other);         
    BitcoinExchange& operator=(const BitcoinExchange& other); 
    ~BitcoinExchange();                                   

   
    void processInputFile(const std::string& inputFile);
    double getExchangeRate(const std::string& date) const;


    bool isValidDate(const std::string& date) const;
    bool isValidValue(const double value) const;
    std::string findClosestDate(const std::string& date) const;
    void loadDatabase(const std::string& filename);
    bool getYearMonthDay(const std::string& date, int& year, int& month, int& day) const;
    std::string trim(const std::string& str) const;
    
   
    class FileError : public std::exception 
    {
        public:
            const char* what() const throw() 
            {
                return "Error: could not open file.";
            }
    };
    
    class DateError : public std::exception 
    {
        public:
            const char* what() const throw() 
            {
                return "Error: bad input => ";
            }
    };
    
    class ValueError : public std::exception 
    {
        public:
            const char* what() const throw() 
            {
                return "Error: not a positive number.";
            }
    };
    
    class RangeError : public std::exception 
    {
        public:
            const char* what() const throw() 
            {
                return "Error: too large a number.";
            }
    };
};

#endif