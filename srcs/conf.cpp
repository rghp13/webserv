/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:22:25 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/02 01:01:44 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/conf.hpp"
conf::conf()//rework this
{
	_Port = 0;
	_MaxBodySize = 0;
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
	_Host = src._Host;
	_Port = src._Port;
	_ServerName = src._ServerName;
	_DefaultError = src._DefaultError;
	_MaxBodySize = src._MaxBodySize;
	_location = src._location;
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
	Error_type tmp;
	if (test == false)
		return (1);
	std::getline(ss, token, ' ');
	while (std::getline(ss, token, ' '))
	{
		tmp.first = std::atoi(token.c_str());
		if (!std::getline(ss, token, ' '))
			return (1);
		tmp.second = token;
		if (tmp.second.empty() || !(tmp.first >= 100 && tmp.first <= 599))
			return (1);
		else
			_DefaultError.push_back(tmp);
	}
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
	if (!std::getline(ss, token, ' '))
		return (1);
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
		else if (token == "PUT")
			loc._methods |= PUT;
		else if (token == "HEAD")
			loc._methods |= HEAD;
		else
			return (1);
	}
	if (loc._methods == 0)
		return (1);
	return (0);
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

	if (test == false)
		return (1);
	std::getline(ss, token, ' ');
	if (!std::getline(ss, token, ' '))
		return (1);
	loc._index = token;
	return (0);
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
	_DefaultError.clear();
	_MaxBodySize = 0;
	_location.clear();
	
}
void	conf::print(void)
{
	std::cout << "===============================================================" << std::endl;
	std::cout << "Config for server: " << _Host << ":" << _Port << std::endl;
	std::cout << "Server Names: ";
	for (std::vector<std::string>::iterator i=_ServerName.begin(); i != _ServerName.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	for (std::vector<Error_type>::iterator ptr = _DefaultError.begin(); ptr != _DefaultError.end(); ptr++)
		std::cout << "Page for error code " << ptr->first << ": " << ptr->second << std::endl;
	std::cout << "Max Body size: " << _MaxBodySize << std::endl;
	for (std::vector<location>::iterator iter = _location.begin(); iter != _location.end(); iter++)
	{
		std::cout << "---------------------------------------------------------------" << std::endl;
		std::cout << "Location Block: " << iter->_path << std::endl;
		std::cout << "Allowed Methods: ";
		if (iter->_methods & GET)
			std::cout << "GET ";
		if (iter->_methods & POST)
			std::cout << "POST ";
		if (iter->_methods & DELETE)
			std::cout << "DELETE ";
		if (iter->_methods & PUT)
			std::cout << "PUT ";
		if (iter->_methods & HEAD)
			std::cout << "HEAD ";
		std::cout << std::endl;
		if (iter->_redirection.first != 0)
			std::cout << "Redirect code" << iter->_redirection.first << " Value " << iter->_redirection.second << std::endl;
		std::cout << "File Root: " << iter->_root << std::endl;
		if (iter->_index.size())
			std::cout << "Default File: " << iter->_index << std::endl;
		std::cout << "Directory Listing Enabled?: " << iter->_autoindex << std::endl;
		std::cout << "CGI executable path for " << iter->_cgi.first << "files: " << iter->_cgi.second << std::endl;
		std::cout << "Upload Directory: " << iter->_uploaddir << std::endl;
	}
	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << "===============================================================" << std::endl;
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
std::vector<Error_type>	conf::get_Default_error(void)const
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
bool	conf::Alias_compare(std::string &src)
{
	for (std::vector<std::string>::iterator i = _ServerName.begin(); i != _ServerName.end(); i++)
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