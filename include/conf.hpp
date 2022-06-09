/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:21:40 by rponsonn          #+#    #+#             */
/*   Updated: 2022/06/09 14:51:04 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
# define CONF_HPP
#include <string>
#include <vector>
//if passed request is for a folder instead of a file return index.html
class conf
{
private:
	int							_Port;//recommmended between 1024-65535
	std::string					_ServerName;//hostname or ip address
	std::vector<std::string>	_ServerAlias;//separate multiple entries with spaces
	std::string					_ServerRoot;//the root of our webserv install
	std::string					_DocumentRoot;//where all docs are stored,if not supplied will default to ServerRoot/htdocs
	unsigned short int			_Method;//method flag GET == 1 POST == 2 DELETE == 4

public:
	conf();
	conf(conf const &src);
	~conf();
	conf	&operator=(conf const &src);
};



#endif