/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:40:14 by rponsonn          #+#    #+#             */
/*   Updated: 2022/06/30 16:54:15 by rponsonn         ###   ########.fr       */
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
	int			flag = 0;
	int			isempty = 1;
	int			error = 0;
	while (!file.eof())
	{
		std::getline(file, line);
		if (line.find("Listen", 0, 6) == 0)
		{
			if (flag++)
			{
				Vconf.push_back(temp);
				temp.clear();
			}
			error |= temp.set_socket(line);
		}
		else if (line.find("ServerName", 0, 10) == 0)
			error |= temp.set_name(line);
		else if (line.find("ServerAlias", 0, 11) == 0)
			error |= temp.set_alias(line);
		else if (line.find("DocumentRoot", 0, 12) == 0)
			error |= temp.set_docroot(line);
		else if (line.find("Method", 0, 6) == 0)
			error |= temp.set_method(line);
		else if (line.find("DirList", 0, 7) == 0)
			error |= temp.set_listing(line);
		else
			continue ;
		isempty = 0;
	}
	file.close();
	if (error || isempty)
	{
		std::cout << "An error was found\n";
		return (1);
	}
	Vconf.push_back(temp);
	return (0);
}

void	RemoveWordString(std::string &line, const std::string &word)
{
	size_t i;
	i = line.find(word);
	if (i != std::string::npos)
		line.erase(i, word.length());
}

int	fill_socket_vector(std::vector<t_socket_info> &socketInitInfo, std::vector<conf> &Vconf)
{
	for (std::vector<conf>::iterator i = Vconf.begin(); i != Vconf.end(); i++)
	{
		{
			t_socket_info	temp;
			temp.host = i->get_Host();
			temp.port = i->get_Port();
			std::cout << "Object created with Host: " << temp.host << " and port#: " << temp.port << std::endl;
			socketInitInfo.push_back(temp);
		}
	}
	return (0);
}
bool	check_duplicate_socket(std::vector<t_socket_info> &socketInitInfo)
{
	for (std::vector<t_socket_info>::iterator first = socketInitInfo.begin(); first != socketInitInfo.end(); first++)
	{
		for (std::vector<t_socket_info>::iterator second = first + 1; second != socketInitInfo.end(); second++)
		{
			if (first->host == second->host && first->port == second->port)
			{
				std::cerr << "Duplicate Entry found, Aborting\n";
				return (true);
			}
		}
	}
	return (false);
}