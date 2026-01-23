/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:16:55 by khadj-me          #+#    #+#             */
/*   Updated: 2025/06/04 16:56:05 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static bool isNumber(std::string str)
{
    std::stringstream ss(str);
    double temp;
    if (!(ss >> temp))
        return false;
    return true;
}

static double toDouble(std::string str)
{
    std::stringstream ss(str);
    double ret;

    ss >> ret;
    return ret;    
}

static bool isEmpty(std::string str)
{
    std::string::iterator end = str.end();
    for (std::string::iterator it = str.begin(); it != end; it++)
        if (*it != ' ')
            return false;
    return true;
}

//-----------------------------//

BitcoinExchange::s_date::s_date() : _year(-1), _month(-1), _day(-1)
{
}

BitcoinExchange::s_date::s_date(double year, double month, double day) : _year(year), _month(month), _day(day)
{
}

bool BitcoinExchange::s_date::operator==(struct s_date& toComp)
{
    return _year == toComp._year && _month == toComp._month && _day == toComp._day;
}

bool BitcoinExchange::s_date::operator>(struct s_date& toComp)
{
    if (_year > toComp._year)
        return true;
    if (_year == toComp._year && _month > toComp._month)
        return true;
    if (_year == toComp._year && _month == toComp._month && _day > toComp._day)
        return true;
    return false;
}

BitcoinExchange::s_dV::s_dV(std::string str, int factor) : _str(str) ,_date()
{
    if (factor == INIT_V && validFormat(str, DONT_PRINT_MSG))
    {
        _date._year = toDouble(str.substr(V_YEAR_POS, 4));
        _date._month = toDouble(str.substr(V_MONTH_POS, 2));
        _date._day = toDouble(str.substr(V_DAY_POS, 2));
        _value = toDouble(str.substr(V_VALUE_POS, std::string::npos));
    }
    else if (factor == INIT_DATA)
    {
        _date._year = toDouble(str.substr(DATA_YEAR_POS, 4));
        _date._month = toDouble(str.substr(DATA_MONTH_POS, 2));
        _date._day = toDouble(str.substr(DATA_DAY_POS, 2));
        _value = toDouble(str.substr(DATA_VALUE_POS, std::string::npos));
    }
}

//------------------------------//

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(std::string file)
{
    std::ifstream db("data.csv");
    if (!db.is_open())
        throw NoDatabaseException();
    std::string temp;
    std::getline(db, temp);
    while (!db.eof())
    {
        std::getline(db, temp);
        if (!isEmpty(temp))
            _data.push_back(t_dV(temp, INIT_DATA));
    }
    std::ifstream ifs(file.c_str());
    if (!ifs.is_open())
        throw FileOpenFailException();
    std::getline(ifs, temp);
    if (temp != "date | value")
        throw FileHeaderException();
    while (!ifs.eof())
    {
        std::getline(ifs, temp);
        if (!isEmpty(temp))
            _v.push_back(t_dV(temp, INIT_V));
    }
    ifs.close();
    db.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& toCopy)
{
    *this = toCopy;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& toAssign)
{
    this->_v = toAssign._v;
    this->_data = toAssign._data;
    return *this;
}

bool BitcoinExchange::validFormat(std::string str, bool prMsg)
{
    if (str.size() < MIN_FORMAT_SIZE ||
        !std::isdigit(str[0]) || 
        !std::isdigit(str[1]) ||
        !std::isdigit(str[2]) ||
        !std::isdigit(str[3]) || 
        str[4] != '-' ||
        !std::isdigit(str[5]) ||
        !std::isdigit(str[6]) ||
        str[7] != '-' ||
        !std::isdigit(str[8]) || 
        !std::isdigit(str[9]) ||
        !isNumber(str.substr(13, std::string::npos)) ||
        str.find("|") != PIPE_POS)
    {
        if (prMsg)
            std::cout << ERROR_BAD_INPUT << str << std::endl;
        return false;
    }
    return true;
}

void BitcoinExchange::validValue(t_dV dV)
{
    if (dV._date._year == -1)
        return (std::cout << ERROR_BAD_INPUT << dV._str << std::endl, (void)0);
    if (dV._date._month > 12 || dV._date._month < 1)
        return (std::cout << ERROR_MONTH_LIM << std::endl, (void)0);
    if (dV._date._day > 31 || dV._date._day < 1)
        return (std::cout << ERROR_DAY_LIM << std::endl, (void)0);
    if (dV._value < 0)
        return (std::cout << ERROR_NOT_POS_NUMBER << std::endl, (void)0);
    if (dV._value > MAX_VALUE)
        return (std::cout << ERROR_MAX_OVERFLOW << std::endl, (void)0);
    bitcoinConvert(dV);
}

void BitcoinExchange::bitcoinConvert(t_dV dV)
{
    std::list<t_dV>::iterator it;
    std::list<t_dV>::iterator end = _data.end();
    if (_data.begin()->_date > dV._date)
        return (std::cout << _data.begin()->_str.substr(0, 10) + " => " << dV._value << " = " << dV._value * _data.begin()->_value << std::endl, (void)0);
    for (it = _data.begin(); it != end; it++)
    {
        if (it->_date == dV._date)
            return (std::cout << dV._str.substr(0, 10) + " => " << dV._value << " = " << dV._value * it->_value << std::endl, (void)0);
        if (it->_date > dV._date)
            return (std::cout << dV._str.substr(0, 10) + " => " << dV._value << " = " << dV._value * (--it)->_value << std::endl, (void)0);
    }
    std::cout << dV._str.substr(0, 10) + " => " << dV._value << " = " << dV._value * (--it)->_value << std::endl;
}

void BitcoinExchange::parseV()
{
    std::list<t_dV>::iterator end = _v.end();
    for (std::list<t_dV>::iterator it = _v.begin(); it != end; it++)
        if (validFormat((*it)._str, PRINT_MSG))
            validValue(*it);
}

const char* BitcoinExchange::FileHeaderException::what() const throw()
{
    return ("Error: header \"date | value\" not present");
}

const char* BitcoinExchange::FileOpenFailException::what() const throw()
{
    return ("Error: couldn't open file");
}

const char* BitcoinExchange::NoDatabaseException::what() const throw()
{
    return ("Error: couldn't open database \"data.csv\"");
}