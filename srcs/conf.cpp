/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:22:25 by rponsonn          #+#    #+#             */
/*   Updated: 2022/06/11 21:37:01 by rponsonn         ###   ########.fr       */
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
	this->_Socket.host = src._Socket.host;
	this->_Socket.port = src._Socket.port;
	this->_ServerAlias = src._ServerAlias;
	this->_ServerName = src._ServerName;
	this->_ServerRoot = src._ServerRoot;
	return (*this);
}
void	conf::set_socket(std::string &input)
{

}