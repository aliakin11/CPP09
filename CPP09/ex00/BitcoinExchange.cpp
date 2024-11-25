#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& databaseFile) 
{
    loadDatabase(databaseFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _database = other._database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}


std::string BitcoinExchange::trim(const std::string& str) const 
{
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

bool BitcoinExchange::getYearMonthDay(const std::string& date, int& year, int& month, int& day) const 
{
    if (date.length() != 10)
        return false;

    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    year = atoi(yearStr.c_str());
    month = atoi(monthStr.c_str());
    day = atoi(dayStr.c_str());

    return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) const 
{
    if (date.length() != 10) 
        return false;
    
    if (date[4] != '-' || date[7] != '-') 
        return false;

    int year, month, day;
    if (!getYearMonthDay(date, year, month, day))
        return false;

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    
    if (month == 2) 
    {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28))
            return false;
    }
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }

    return true;
}

bool BitcoinExchange::isValidValue(const double value) const 
{
    return value >= 0 && value <= 1000;
}

std::string BitcoinExchange::findClosestDate(const std::string& date) const 
{
    std::map<std::string, double>::const_iterator it = _database.upper_bound(date);
    if (it == _database.begin())
        return it->first;
    --it;
    return it->first;
}

void BitcoinExchange::loadDatabase(const std::string& filename) 
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw FileError();

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) 
    {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) 
        {
            std::string date = line.substr(0, commaPos);
            std::string value = line.substr(commaPos + 1);
            
            if (isValidDate(date))
                _database[date] = atof(value.c_str());
        }
    }
    file.close();
}

void BitcoinExchange::processInputFile(const std::string& inputFile) {
    std::ifstream file(inputFile.c_str());
    if (!file.is_open())
        throw FileError();

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) 
    {
        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos) 
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, pipePos));
        std::string valueStr = trim(line.substr(pipePos + 1));

        if (!isValidDate(date)) 
        {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }

        char* endPtr;
        double value = strtod(valueStr.c_str(), &endPtr);
        if (*endPtr != '\0') 
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (!isValidValue(value)) 
        {
            if (value < 0)
                std::cout << "Error: not a positive number." << std::endl;
            else
                std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        std::string closestDate = findClosestDate(date);
        double rate = _database[closestDate];
        std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
    }
    file.close();
}

double BitcoinExchange::getExchangeRate(const std::string& date) const 
{
    std::map<std::string, double>::const_iterator it = _database.find(date);
    if (it != _database.end())
        return it->second;
    return _database.at(findClosestDate(date));
}