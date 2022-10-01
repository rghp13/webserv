/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_GET.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:46:31 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/01 18:40:06 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

std::vector<conf>::iterator	strict_scan(std::vector<conf> &Vconf, Request &src) //need conf.cpp to be done before changing
{
	std::vector<conf>::iterator i;
	for (i = Vconf.begin(); i != Vconf.end(); i++)
	{
		if (i->get_Port() == src._port && i->get_Host() == src._host)
		{
			if (i->Alias_compare(src._domain))
				break;
		}
	}
	return (i);
}
std::vector<conf>::iterator	non_strict_scan(std::vector<conf> &Vconf, Request &src) //need conf.cpp to be done before changing
{
	std::vector<conf>::iterator i;
	for (i = Vconf.begin(); i != Vconf.end(); i++)
	{
		if ((i->get_Port() == src._port || 0 == i->get_Port()) && (i->get_Host() == "*" || i->get_Host() == src._host))
		{
			if (i->Alias_compare(src._domain))
				return (i);
		}
	}
	for (i = Vconf.begin(); i != Vconf.end(); i++)
	{
		if ((i->get_Port() == src._port || 0 == i->get_Port()) && (i->get_Host() == "*" || i->get_Host() == src._host))
		{
			return (i);
		}
	}
	return (i);
}

Answer	process_get(Request &src, std::vector<conf>::iterator iter, location location)//need to talk about arguments
{
	std::ifstream				file;
	Answer						ret;
	std::string					path;
	std::string					buffer;

	(void)iter; //we'll need it for CGI
	if (src.isPageADirectory())
	{
		if (location._autoindex)
		{
			ret._Body = generateDirectoryPage(src._Path, location._root);
			return (ret);
		}
		path = location._root + src._Path;
		if (access(path.c_str(), F_OK))
			return (Answer(404));
		if (access(path.c_str(), R_OK))//testing if folder prior to index.html can 
			return (Answer(403));
		path += "index.html";
		if (access(path.c_str(), F_OK))
			return (Answer(404));
		if (access(path.c_str(), R_OK))
			return (Answer(403));
	}
	else
	{
		src.htmlize();
		path = location._root + src._Path;
		if (access(path.c_str(), F_OK))
			return (Answer(404));
		if (access(path.c_str(), R_OK))
			return (Answer(403));//probably triggers if permission issue
	}
	file.open(path.c_str());
	while (std::getline(file, buffer))
	{
		ret._Body += buffer;
		ret._Body += HTTPNL;//double check if this is necessary
	}
	file.close();
	return (ret);
}