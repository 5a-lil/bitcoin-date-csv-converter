/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:06:37 by khadj-me          #+#    #+#             */
/*   Updated: 2025/06/04 16:13:02 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <list>
#include <iterator>
#include <exception>

// RANDOM DEFINES
#define DONT_PRINT_MSG false
#define PRINT_MSG true
#define MAX_VALUE 1000

// DELIMITATIONS
#define MIN_FORMAT_SIZE 14
#define PIPE_POS 11
    //_v
    #define V_YEAR_POS 0
    #define V_MONTH_POS 5
    #define V_DAY_POS 8
    #define V_VALUE_POS 13
    //_data
    #define DATA_YEAR_POS 0
    #define DATA_MONTH_POS 5
    #define DATA_DAY_POS 8
    #define DATA_VALUE_POS 11

// ERROR MESSAGES
#define ERROR_BAD_INPUT "Error: bad input => "
#define ERROR_YEAR_LIM "Error: input a year between 2010 and 2022."
#define ERROR_MONTH_LIM "Error: input a month between 1 and 12."
#define ERROR_DAY_LIM "Error: input a month between 1 and 31."
#define ERROR_NOT_POS_NUMBER "Error: not a positive number."
#define ERROR_MAX_OVERFLOW "Error: too large a number."

// INITS
#define INIT_DATA 1
#define INIT_V 2

class BitcoinExchange
{
    private:
        typedef struct s_date
        {
            double _year;    
            double _month;
            double _day;
            s_date();
            s_date(double year, double month, double day);
            bool operator==(struct s_date& toComp);
            bool operator>(struct s_date& toComp);
        } t_date;
        typedef struct s_dV
        {
            std::string _str;
            t_date _date;
            double _value;
            s_dV(std::string str, int factor);
        } t_dV;
        std::list<t_dV> _v;
        std::list<t_dV> _data;
        BitcoinExchange();

        class FileHeaderException : public std::exception
        {
            public:
                const char* what() const throw ();
        };

        class NoDatabaseException : public std::exception
        {
            public:
                const char* what() const throw ();
        };
    public:
        BitcoinExchange(std::string file);
        BitcoinExchange(const BitcoinExchange& toCopy);
        ~BitcoinExchange();

        BitcoinExchange& operator=(const BitcoinExchange& toAssign);

        std::list<std::string> getV();

        static bool validFormat(std::string str, bool prMsg);
        void validValue(t_dV dV);
        void bitcoinConvert(t_dV dV);
        void parseV();
        
        class FileOpenFailException : public std::exception
        {
            public:
                const char* what() const throw ();
        };
};