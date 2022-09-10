/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:15:57 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/10 16:04:02 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Request.hpp"

Request::Request()
{
	_port = 0;
	_host = "*";
	_domain = "";
	_Path = "";
	_malformed = false;
}

Request::Request(unsigned int newport, std::string newhost, std::string header)//add a test to see if it's valid
{
	_port = newport;
	_host = newhost;
	_malformed = false;
	//parse the header here
	header.erase(std::remove(header.begin(), header.end(), '\r'), header.end());
	std::stringstream ss(header);
	std::string token;
	std::getline(ss, token, '\n');
	{
		std::stringstream subs(token);
		std::getline(subs, _Method, ' ');//Think about how to handle a simple newline entry
		std::getline(subs, _Path, ' ');//
		ascii_codes(_Path);
		std::getline(subs, _Version, ' ');//
		if (_Method.empty() || _Path.empty() || _Version.empty())
			_malformed = true;
	}
	while (std::getline(ss, token, '\n'))
	{
		if (token.length() == 0)
			break;
		std::stringstream subs(token);
		t_header_argument tmp;
		std::getline(subs, tmp.key, ' ');
		if (tmp.key.find(':')== std::string::npos)
		{
			std::cout << "_______________________\n";
			std::cout << token.length() << std::endl;
			std::cout << token << std::endl;
			std::cout << tmp.key << std::endl;
			_malformed = true;//malformed
		}
		std::getline(subs, tmp.value, ' ');//check if these are valid
		AddArgument(tmp);
	}
	if (find_key("Content-Length:"))
		std::getline(ss, _Body);
}
Request::Request(Request const &src)
{
	*this = src;
}
Request &Request::operator=(Request const &src)
{
	_port = src._port;
	_host = src._host;
	_domain = src._domain;
	_Method = src._Method;
	_Path = src._Path;
	_Version = src._Version;
	_Arguments = src._Arguments;
	_Body = src._Body;
	return (*this);
}
bool	Request::find_key(std::string key)
{
	std::vector<t_header_argument>::iterator it = _Arguments.begin();
	while (it != _Arguments.end())
	{
		if (it->key == key)
			return (true);
		++it;
	}
	return (false);
}
void	Request::AddArgument(t_header_argument newArg)
{
	//check if key is already in
	std::vector<t_header_argument>::iterator it = _Arguments.begin();
	while (it != _Arguments.end())
	{
		if (newArg.key == it->key)
		{
			it->value = newArg.value;
			return;
		}
		it++;
	}
	_Arguments.push_back(newArg);
}

bool	Request::isPageADirectory( void ) const
{
	return (_Path.at(_Path.length() - 1) == '/');
}

Request::~Request()
{
}
void	Request::htmlize(void)
{
	//This is problematic
	if (_Path.find('.') != _Path.npos)
		return ;
	std::string html = ".html";
	if (_Path.find(html.c_str(), _Path.size() - html.size(), html.size()) == std::string::npos)
		_Path += html;
}