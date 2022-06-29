/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:22:25 by rponsonn          #+#    #+#             */
/*   Updated: 2022/06/29 17:25:11 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/conf.hpp"
#define GET 0b1
#define POST 0b10
#define DELETE 0b100
conf::conf()
{
	_Port = 0;
	_Method = 0;
}
conf::conf(conf const &src)
{
	*this = src;
}
conf::~conf()
{
	;
}
conf	&conf::operator=(conf const &src)
{
	if (this == &src)
		return (*this);
	this->_DocumentRoot = src._DocumentRoot;
	this->_Method = src._Method;
	this->_Host = src._Host;
	this->_Port = src._Port;
	this->_ServerAlias = src._ServerAlias;
	this->_ServerName = src._ServerName;
	this->_ServerRoot = src._ServerRoot;
	return (*this);
}
int	conf::set_socket(std::string &input)
{
	std::string	delimiter = ":";
	std::string	token;
	size_t		i = 0;
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
int	conf::set_name(std::string &line)
{
	std::string	token;
	std::stringstream	ss(line);
	std::getline(ss, token, ' ');
	std::getline(ss, token, ' ');
	_ServerName = token;
	if (token == "ServerName")
		return (1);
	return (0);
}
int	conf::set_alias(std::string &line)
{
	std::string			token;
	std::stringstream	ss(line);
	bool				loop = false;
	std::getline(ss, token, ' ');
	while (std::getline(ss, token, ' '))//rework this to be in a loop
	{
		loop = true;
		_ServerAlias.push_back(token);
	}
	if (loop == false)
		return (1);
	return (0);
}
int	conf::set_docroot(std::string &line)
{
	std::string			token;
	std::stringstream	ss(line);

	std::getline(ss, token, ' ');
	if (!(std::getline(ss, token, ' ')))
		return (1);
	_DocumentRoot = token;
	return (0);
}
int	conf::set_method(std::string &line)
{
	std::string			token;
	std::stringstream	ss(line);
	bool				loop = false;

	std::getline(ss, token, ' ');
	while (std::getline(ss, token, ' '))
	{
		if (token == "GET")
			_Method |= GET;
		else if (token == "POST")
			_Method |= POST;
		else if (token == "DELETE")
			_Method |= DELETE;
		else
			return (1);
		loop = true;
	}
	if (loop)
		return (0);
	return (1);
}
void	conf::clear(void)
{
	_Host.clear();
	_Port = 0;
	_ServerName.clear();
	_ServerAlias.clear();
	_ServerRoot.clear();
	_DocumentRoot.clear();
	_Method = 0;
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
}
std::string	conf::get_Host(void)const
{
	return (_Host);
}
unsigned int conf::get_Port(void)const
{
	return(_Port);
}
std::string	conf::get_ServerName(void)const
{
	return (_ServerName);
}
bool	conf::Alias_compare(std::string &src)
{
	for (std::vector<std::string>::iterator i = _ServerAlias.begin(); i != _ServerAlias.end(); i++)
	{
		if (*i == src)
			return (true);
	}
	return (false);
}