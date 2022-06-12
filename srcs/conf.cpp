/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:22:25 by rponsonn          #+#    #+#             */
/*   Updated: 2022/06/13 00:09:28 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/conf.hpp"
conf::conf()
{
	;
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
	RemoveWordString(input, "listen");
	RemoveWordString(input, " ");
	RemoveWordString(input, "\t");
	if ((i = input.find(delimiter)) == std::string::npos)
		return (1);
	token = input.substr(0, i);
	_Host = token;
	token = input.substr(i + 1);
	_Port = std::atoi(token.c_str());
	return (0);
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