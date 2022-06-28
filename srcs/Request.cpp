/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:15:57 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/29 00:31:13 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Request.hpp"

Request::Request()
{
	port = 0;
	host = "*";
	domain = "";
	pageRequested = "";
}

Request::Request(int newport, std::string newhost, std::string newdomain, std::string newpage)
{
	port = newport;
	host = newhost;
	domain = newdomain;
	pageRequested = newpage;
}

Request::Request(int newport, std::string newhost, std::string newdomain)
{
	port = newport;
	host = newhost;
	domain = newdomain;
	pageRequested = "/";
}

bool	Request::isPageADirectory( void ) const
{
	return (pageRequested.at(pageRequested.length() - 1) == '/');
}

Request::~Request()
{
}
