/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:10:15 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/07 19:38:12 by dimitriscr       ###   ########.fr       */
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
	std::string	domain;
	std::string	pageRequested;
	Request();
	Request(int newport, std::string newdomain, std::string newpage);
	Request(int newport, std::string newdomain);
	bool	isPageADirectory( void ) const;
	~Request();
};

#endif