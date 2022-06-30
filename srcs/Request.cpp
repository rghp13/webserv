/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:15:57 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/30 21:40:25 by rponsonn         ###   ########.fr       */
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

Request::Request(unsigned int newport, std::string newhost, std::string newdomain, std::string newpage)
{
	port = newport;
	host = newhost;
	domain = newdomain;
	pageRequested = newpage;
}

Request::Request(unsigned int newport, std::string newhost, std::string newdomain)
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
void	Request::htmlize(void)
{
	std::string html = ".html";
	if (pageRequested.find(html.c_str(), pageRequested.size() - html.size(), html.size()) == std::string::npos)
		pageRequested += html;
}