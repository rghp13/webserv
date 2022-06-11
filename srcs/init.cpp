/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:40:14 by rponsonn          #+#    #+#             */
/*   Updated: 2022/06/11 20:40:09 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

bool boot_check(int argc, char **argv, std::ifstream &argfile)//return true if something is wrong with args
{
	if (argc > 2)
	{
		std::cerr << "Error: Too many ARGS\n";
		return (1);
	}
	else if (argc == 2)
	{
		if (!access(argv[1], R_OK))
		{
			argfile.open(argv[1]);
			std::cout << "File exists and can be read from\n";
		}
		else
		{
			std::cout <<"File doesn't exist or can't be read from\n";
			return (1);
		}
	}
	else
	{
		if (!access("test.conf", R_OK))
		{
			argfile.open("/home/romain/Documents/webserv/test.conf");
			std::cout << "opened file\n";
		}
		else
			std::cout << "couldn't find default file\n";
	}
	return (0);
}

int	init(std::vector<conf> &Vconf, std::ifstream &file)//read from file match to variable and fill out object
{
	std::string	line;
	conf		temp;
	while (!file.eof())
	{
		std::getline(file, line);
		
	}
	file.close();
	return (0);
}