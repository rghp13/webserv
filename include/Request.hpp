/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:10:15 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/29 00:31:17 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
 #define REQUEST_HPP
#include <string>

class Request
{
private:

public:
	int			port;
	std::string	host;
	std::string	domain;
	std::string	pageRequested;
	Request();
	Request(int newport, std::string newhost, std::string newdomain, std::string newpage);
	Request(int newport, std::string newhost, std::string newdomain);
	bool	isPageADirectory( void ) const;
	~Request();
};

#endif