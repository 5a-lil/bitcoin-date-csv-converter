/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khadj-me <khalilhadjmes1@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:05:49 by khadj-me          #+#    #+#             */
/*   Updated: 2025/06/01 19:08:01 by khadj-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    (void)argc;
    try
    {
        if (!argv[1])
            throw BitcoinExchange::FileOpenFailException();
        BitcoinExchange btc(argv[1]);
        
        btc.parseV();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}