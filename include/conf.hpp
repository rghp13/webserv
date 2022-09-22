/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:21:40 by rponsonn          #+#    #+#             */
/*   Updated: 2022/09/23 00:49:36 by rponsonn         ###   ########.fr       */
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
//reworking conf
//server is keyword to create new conf
//location is sub-struct
//Method [list of methods]
//Redirect [code] [path]
//Root [path]
//Index [list of index files]vector
//Autoindex [on or off]
//cgi_pass [file extension] [path of the cgi script]
//upload_store [directory]

//note to self, if returning a referrence, do some tests as to how to properly recieve it
class conf
{
private:
	std::string					_Host;
	unsigned int				_Port;//recommmended between 1024-65535
	std::vector<std::string>	_ServerName;//hostname or ip address
	Error_type					_DefaultError;//Code/path
	//std::string				_ServerRoot;//the root of our webserv instal
	//bool						_ListingEnabled;//removing
	unsigned long int			_MaxBodySize;
	//t_redirect				_redirect;//removing
	std::vector<location>		_location;


public:
	conf();
	conf(conf const &src);
	~conf();
	conf						&operator=(conf const &src);
	int							set_socket(std::string &input);//host and port covered here
	int							set_name(std::string &line);//now stored as a vector
	int							set_default_error(std::string &line);
	int							set_alias(std::string &line);//remove
	int							set_method(std::string &line);//remove
	int							set_max_size(std::string &line);

	int							set_location_path(std::string &line, location &loc);
	int							set_location_methods(std::string &line, location &loc);
	int							set_location_redirect(std::string &line, location &loc);
	int							set_location_docroot(std::string &line, location &loc);
	int							set_location_auto_listing(std::string &line, location &loc);
	int							set_location_index(std::string &line, location &loc);
	int							set_location_cgi(std::string &line, location &loc);
	int							set_redirection(std::string &line);//should this be gone?

	std::string					get_Host(void)const;
	unsigned int				get_Port(void)const;
	std::vector<std::string>	get_ServerName(void)const;//updated from string to vector
	Error_type					get_Default_error(void)const;
	unsigned long int			get_MaxSize(void)const;
	std::vector<location>		get_location(void)const;
	bool						Alias_compare(std::string &src);//why did I code this
	void						print(void);
	void						clear(void);
};



#endif