/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:40:14 by rponsonn          #+#    #+#             */
/*   Updated: 2022/09/25 16:03:12 by rponsonn         ###   ########.fr       */
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
	location	loc;
	bool		flag = false;
	bool		locflag = false;
	int			isempty = 1;
	int			error = 0;

	location_clear(loc);
	while (!file.eof())
	{
		if (error)
		{
			std::cout << "Triggered break check on line" << std::endl;
			std::cout << line << std::endl;
			break;
		}
		std::getline(file, line);
		if (line == "Server")
		{
			if (flag)
			{
				if (locflag)
					temp.push_loc(loc);
				error |= check_locroot(temp);//will scan all locs for a root that's just /
				Vconf.push_back(temp);
				temp.clear();
				locflag = false;
				location_clear(loc);
			}
			else
				flag = true;
		}
		else if (line.find("Location ", 0, 9) == 0)
		{
			if (locflag)
			{
				temp.push_loc(loc);
				location_clear(loc);
			}
			else
				locflag = true;
			error |= temp.set_location_path(line, loc);
		}
		else if (line.find("Listen ", 0, 7) == 0)
			error |= temp.set_socket(line, flag);
		else if (line.find("ServerName ", 0, 11) == 0)
			error |= temp.set_name(line, flag);
		else if (line.find("DefaultError ", 0, 13) == 0)
			error |= temp.set_default_error(line, flag);
		else if (line.find("MaxSize ",0 , 8) == 0)
			error |= temp.set_max_size(line, flag);//last server block
		else if (line.find("Method ", 0, 7) == 0)
			error |= temp.set_location_methods(line, loc, locflag);
		else if (line.find("Redirect ",0, 9) == 0)
			error |= temp.set_location_redirect(line, loc, locflag);
		else if (line.find("Root ", 0, 5) == 0)
			error |= temp.set_location_docroot(line, loc, locflag);
		else if (line.find("DirList ", 0, 8) == 0)
			error |= temp.set_location_auto_listing(line, loc, locflag);
		else if (line.find("Index ", 0, 6) == 0)
			error |= temp.set_location_index(line, loc, locflag);
		else if (line.find("CGI ", 0, 4) == 0)
			error |= temp.set_location_cgi(line, loc, locflag);
		else if (line.find("UploadDir ", 0, 10) == 0)
			error |= temp.set_location_upload_path(line, loc, locflag);
		else
			continue ;
		isempty = 0;
	}
	file.close();
	if (error/* || isempty*/)
	{
		std::cout << "An error was found\n";
		std::cout << line << std::endl;
		temp.print();
		return (1);
	}
	else if (isempty)
	{
		std::cout << "empty file\n";
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