/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:10:15 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/29 23:29:26 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
 #define REQUEST_HPP
#include <string>

class Request
{
private:

public:
	unsigned int	port;
	std::string		host;
	std::string		domain;
	std::string		pageRequested;
	Request();
	Request(unsigned int newport, std::string newhost, std::string newdomain, std::string newpage);
	Request(unsigned int newport, std::string newhost, std::string newdomain);
	bool	isPageADirectory( void ) const;
	~Request();
};

#endif