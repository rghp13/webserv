/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:10:15 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/04 22:18:10 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
 #define REQUEST_HPP
#include <string>
#include <algorithm>
#include "webserv.hpp"

class Request
{
private:
public:
	unsigned int					_port;
	std::string						_host;
	std::string						_domain;
	std::string						_Method;
	std::string						_Path;
	std::string						_Version;
	std::vector<t_header_argument>	_Arguments;
	std::string						_Body;
	Request();
	Request(unsigned int newport, std::string newhost, std::string newdomain, std::string newpage);
	Request(unsigned int newport, std::string newhost, std::string newdomain);
	bool	isPageADirectory( void ) const;
	void	htmlize(void);
	~Request();
};

#endif