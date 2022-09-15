/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:21:40 by rponsonn          #+#    #+#             */
/*   Updated: 2022/09/14 15:18:45 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
# define CONF_HPP
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "webserv.hpp"
//if passed request is for a folder instead of a file return index.html
class conf
{
private:
	std::string					_Host;
	unsigned int				_Port;//recommmended between 1024-65535
	std::string					_ServerName;//hostname or ip address
	std::vector<std::string>	_ServerAlias;//separate multiple entries with spaces
	std::string					_ServerRoot;//the root of our webserv install
	std::string					_DocumentRoot;//where all docs are stored,if not supplied will default to ServerRoot/htdocs
	unsigned short int			_Method;//method flag GET == 1 POST == 2 DELETE == 4
	bool						_ListingEnabled;
	unsigned long int			_MaxBodySize;
	t_redirect					_redirect;


public:
	conf();
	conf(conf const &src);
	~conf();
	conf						&operator=(conf const &src);
	int							set_socket(std::string &input);
	int							set_name(std::string &line);
	int							set_alias(std::string &line);
	int							set_docroot(std::string &line);
	int							set_method(std::string &line);
	int							set_listing(std::string &line);
	int							set_redirect(std::string &line);
	int							set_max_size(std::string &line);
	std::string					get_Host(void)const;
	unsigned int				get_Port(void)const;
	std::string					get_ServerName(void)const;
	std::string					get_ServerRoot(void)const;
	std::string					get_DocumentRoot(void)const;
	unsigned short int			get_Method(void)const;
	bool						get_listing(void)const;
	unsigned long int			get_MaxSize(void)const;
	t_redirect					get_redirect(void)const;
	bool						Alias_compare(std::string &src);
	void						print(void);
	void						clear(void);
};



#endif