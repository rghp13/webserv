/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:21:40 by rponsonn          #+#    #+#             */
/*   Updated: 2022/09/21 22:47:51 by rponsonn         ###   ########.fr       */
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
typedef std::pair<int, std::string>			Error_type, Redirect_type;
typedef std::pair<std::string, std::string>	Cgi_type;

struct location
{
	
	std::string					path;		// location
	std::vector<std::string>	methods;	// GET POST DELETE
	Redirect_type				redirection;
	std::string					root;		// new docroot
	std::vector<std::string>	index;		// default file to answer if the request is a directory
	bool						autoindex;	// turn on or off directory listing
	Cgi_type					cgi;		// execute the cgi program
	std::string					uploadStore;// execute the cgi program
};
class conf
{
private:
	std::string					_Host;
	unsigned int				_Port;//recommmended between 1024-65535
	std::string					_ServerName;//hostname or ip address
	std::vector<std::string>	_ServerAlias;//separate multiple entries with spaces
	Error_type					_DefaultError;//Code/path
	//std::string				_ServerRoot;//the root of our webserv instal
	//bool						_ListingEnabled;//removing
	unsigned long int			_MaxBodySize;
	//t_redirect					_redirect;//removing
	std::vector<location>		_location;


public:
	conf();
	conf(conf const &src);
	~conf();
	conf						&operator=(conf const &src);
	int							set_socket(std::string &input);
	int							set_name(std::string &line);
	int							set_alias(std::string &line);
	int							set_docroot(std::string &line);//no longer exists
	int							set_method(std::string &line);
	int							set_listing(std::string &line);
	int							set_redirect(std::string &line);
	int							set_max_size(std::string &line);
	std::string					get_Host(void)const;
	unsigned int				get_Port(void)const;
	std::vector<std::string>	&get_ServerName(void)const;//updated from string to vector
	//std::string				get_ServerRoot(void)const;
	//std::string				get_DocumentRoot(void)const;
	//unsigned short int		get_Method(void)const;
	//bool						get_listing(void)const;
	unsigned long int			get_MaxSize(void)const;
	//t_redirect				get_redirect(void)const;
	std::vector<location>		&get_location(void)const;
	bool						Alias_compare(std::string &src);//why did I code this
	void						print(void);
	void						clear(void);
};



#endif