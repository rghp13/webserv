/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:15:57 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/07 19:44:05 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request()
{
	port = 0;
	domain = "";
	pageRequested = "";
}

Request::Request(int newport, std::string newdomain, std::string newpage)
{
	port = newport;
	domain = newdomain;
	pageRequested = newpage;
}

Request::Request(int newport, std::string newdomain)
{
	port = newport;
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
