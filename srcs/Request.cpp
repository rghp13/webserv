/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:15:57 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/04 22:16:59 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Request.hpp"

Request::Request()
{
	_port = 0;
	_host = "*";
	_domain = "";
	_Path = "";
}

Request::Request(unsigned int newport, std::string newhost, std::string newdomain, std::string newpage)
{
	_port = newport;
	_host = newhost;
	_domain = newdomain;
	_Path = newpage;
}

Request::Request(unsigned int newport, std::string newhost, std::string newdomain)
{
	_port = newport;
	_host = newhost;
	_domain = newdomain;
	_Path = "/";
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
	std::string html = ".html";
	if (_Path.find(html.c_str(), _Path.size() - html.size(), html.size()) == std::string::npos)
		_Path += html;
}