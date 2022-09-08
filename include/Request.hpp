/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:10:15 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/07 16:56:56 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
 #define REQUEST_HPP
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
	bool							_malformed;
	Request();
	Request(unsigned int newport, std::string newhost, std::string header);
	Request(Request const &src);
	~Request();
	Request &operator=(Request const &src);
	bool	isPageADirectory( void ) const;
	void	htmlize(void);//TODO: remember what this was supposed to do
	void	AddArgument (t_header_argument newArg);//adds variables in a key/pair way
	void	parse_header(std::string header);
	bool	find_key(std::string key);
};

#endif