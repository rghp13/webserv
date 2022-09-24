/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:22:25 by rponsonn          #+#    #+#             */
/*   Updated: 2022/09/24 15:39:11 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/conf.hpp"
conf::conf()//rework this
{
	_Port = 0;
	_Method = 0;
	_ListingEnabled = false;
	_redirect.code = 0;
}
conf::conf(conf const &src)
{
	*this = src;
}
conf::~conf()
{
	;
}
conf	&conf::operator=(conf const &src)//will need an update
{
	if (this == &src)
		return (*this);
	clear();
	_DocumentRoot = src._DocumentRoot;
	_Method = src._Method;
	_Host = src._Host;
	_Port = src._Port;
	_ServerAlias = src._ServerAlias;
	_ServerName = src._ServerName;
	_ServerRoot = src._ServerRoot;
	_ListingEnabled = src._ListingEnabled;
	_redirect.code = src._redirect.code;
	_redirect.value = src._redirect.value;
	_MaxBodySize = src._MaxBodySize;
	return (*this);
}
//
//server block
//
int	conf::set_socket(std::string &input, bool test)//host and port is set here
{
	std::string	delimiter = ":";
	std::string	token;
	size_t		i = 0;

	if (test == false)
		return (1);
	RemoveWordString(input, "Listen");
	RemoveWordString(input, " ");
	if ((i = input.find(delimiter)) == std::string::npos)
		return (1);
	token = input.substr(0, i);
	_Host = token;
	token = input.substr(i + 1);
	_Port = std::atoi(token.c_str());
	if (_Host.size() == 0 || token.size() == 0)
		return (1);
	return (0);
}
int	conf::set_name(std::string &line, bool test)//now in vector form
{
	std::string	token;
	std::stringstream	ss(line);
	if (test == false)
		return (1);
	std::getline(ss, token, ' ');
	while (std::getline(ss, token, ' '))
		_ServerName.push_back(token);
	if (token == "ServerName")
		return (1);
	return (0);
}
int	conf::set_default_error(std::string &line, bool test)
{
	std::string token;
	std::stringstream ss(line);
	if (test == false)
		return (1);
	std::getline(ss, token, ' ');
	std::getline(ss, token, ' ');
	_DefaultError.first = std::atoi(token.c_str());
	std::getline(ss, token, ' ');
	_DefaultError.second = token;
	if (_DefaultError.second.empty() || !(_DefaultError.first >= 100 && _DefaultError.first <= 599))
		return (1);
	return (0);
}
int	conf::set_max_size(std::string &line, bool test)
{
	std::string token;
	std::stringstream ss(line);
	std::string::iterator iter;
	unsigned long int x;

	if (test == false)
		return (1);
	std::getline(ss, token, ' ');
	if (!(std::getline(ss, token, ' ')) || token.length() < 2)
		return (1);
	x = std::atoi(token.c_str());
	iter = token.begin();
	if (iter[token.length() - 1] == 'B')
		_MaxBodySize = x;
	else if (iter[token.length() - 1] == 'K')
		_MaxBodySize = KB(x);
	else if (iter[token.length() - 1] == 'M')
		_MaxBodySize = MB(x);
	else if (iter[token.length() - 1] == 'G')
		_MaxBodySize = GB(x);
	else
		return (1);
	return (0);
	
}
//
//Location block
//
int	conf::set_location_path(std::string &line, location &loc)
{
	std::string token;
	std::stringstream ss(line);
	std::getline(ss, token, ' ');
	loc._path = token;
	if (loc._path.empty())
		return (1);
	return (0);
}
int	conf::set_location_methods(std::string &line, location &loc, bool test)
{
	std::string			token;
	std::stringstream	ss(line);

	if (test == false)
		return (1);
	std::getline(ss, token, ' ');
	while (std::getline(ss, token, ' '))
	{
		if (token == "GET")
			loc._methods |= GET;
		else if (token == "POST")
			loc._methods |= POST;
		else if (token == "DELETE")
			loc._methods |= DELETE;
		else
			return (1);
	}
	if (loc._methods == 0)
		return (1);
	return (1);
}
int	conf::set_location_redirect(std::string &line, location &loc, bool test)
{
	std::string token;
	std::stringstream ss(line);

	if  (test == false)
		return (1);
	std::getline(ss, token, ' ');
	if (!(std::getline(ss, token, ' ')))
		return (1);
	loc._redirection.first = std::atoi(token.c_str());
	if (loc._redirection.first < 100 || loc._redirection.first > 599)
		return (1);
	if (!(std::getline(ss, token, ' ')))
		return (1);
	loc._redirection.second = token;
	return (0);
}
int	conf::set_location_docroot(std::string &line, location &loc, bool test)//renamed to be location dependent
{
	std::string			token;
	std::stringstream	ss(line);

	if (test == false)
		return (1);
	std::getline(ss, token, ' ');
	if (!(std::getline(ss, token, ' ')))
		return (1);
	loc._root = token;
	return (0);
}
int	conf::set_location_auto_listing(std::string &line, location &loc, bool test)
{
	std::string			token;
	std::stringstream	ss(line);

	if (test == false)
		return (1);
	std::getline(ss, token, ' ');
	if (!(std::getline(ss, token, ' ')))
		return (1);
	if (token == "true")
		loc._autoindex = true;
	return (0);
}
int	conf::set_location_index(std::string &line, location &loc, bool test)
{
	std::string			token;
	std::stringstream	ss(line);
	bool				loop = false;

	if (test == false)
		return (1);
	std::getline(ss, token, ' ');
	while (std::getline(ss, token, ' '))
	{
		loop = true;
		loc._index.push_back(token);
	}
	if (loop == true)
		return (0);
	return (1);
}
int	conf::set_location_cgi(std::string &line, location &loc, bool test)
{
	std::string			token;
	std::stringstream	ss(line);

	if(test == false)
		return (1);
	std::getline(ss, token, ' ');
	if (!std::getline(ss, token, ' '))
		return (1);
	loc._cgi.first = token;
	if (!std::getline(ss, token, ' '))
		return (1);
	loc._cgi.second = token;
	return (0);
}
int	conf::set_location_upload_path(std::string &line, location &loc, bool test)
{
	std::string			token;
	std::stringstream	ss(line);

	if (test == false)
		return (1);
	std::getline(ss, token, ' ');
	if (!std::getline(ss, token, ' '))
		return (1);
	if (access(token.c_str(), W_OK))
		return (1);
	loc._uploaddir = token;
	return (0);
}

//
//Utilities
//
void	conf::clear(void)
{
	_Host.clear();
	_Port = 0;
	_ServerName.clear();
	_DefaultError.first = 0;
	_DefaultError.second.clear();
	_MaxBodySize = 0;
	_location.clear();
	
}
void	conf::print(void)
{
	std::cout << "Host address is: " << _Host << std::endl;
	std::cout << "Socket number: " << _Port << std::endl;
	std::cout << "Server Name: " << _ServerName << std::endl;
	std::cout << "Alias list: ";
	for (std::vector<std::string>::iterator i=_ServerAlias.begin(); i != _ServerAlias.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "Docroot: " << _DocumentRoot << std::endl;
	std::cout << "Methods: ";
	if (_Method & GET)
		std::cout << "GET ";
	if (_Method & POST)
		std::cout << "POST ";
	if (_Method & DELETE)
		std::cout << "DELETE ";
	std::cout << std::endl;
	std::cout << "Listing enabled: " << _ListingEnabled << std::endl;
	std::cout << "Redirect code" << _redirect.code << " Value " << _redirect.value << std::endl;
	std::cout << "Max Body size = " << _MaxBodySize << std::endl;

}
std::string	conf::get_Host(void)const
{
	return (_Host);
}
unsigned int conf::get_Port(void)const
{
	return(_Port);
}
std::vector<std::string>	conf::get_ServerName(void)const
{
	return (_ServerName);
}
Error_type	conf::get_Default_error(void)const
{
	return (_DefaultError);
}
unsigned long int	conf::get_MaxSize(void)const
{
	return (_MaxBodySize);
}
std::vector<location>	conf::get_location(void)const
{
	return (_location);
}
bool	conf::Alias_compare(std::string &src)//where is this being used?
{
	for (std::vector<std::string>::iterator i = _ServerAlias.begin(); i != _ServerAlias.end(); i++)
	{
		if (*i == src)
			return (true);
	}
	return (false);
}
void	conf::push_loc(location &loc)
{
	_location.push_back(loc);
}