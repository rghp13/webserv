/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_request.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:46:31 by rponsonn          #+#    #+#             */
/*   Updated: 2022/09/06 16:39:59 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

std::vector<conf>::iterator	strict_scan(std::vector<conf> &Vconf, Request &src)
{
	std::vector<conf>::iterator i;
	for (i = Vconf.begin(); i != Vconf.end(); i++)
	{
		if (i->get_Port() == src._port && i->get_Host() == src._host)
		{
			if (src._domain == i->get_ServerName() || i->Alias_compare(src._domain))
				break;
		}
	}
	return (i);
}
std::vector<conf>::iterator	non_strict_scan(std::vector<conf> &Vconf, Request &src)
{
	std::vector<conf>::iterator i;
	for (i = Vconf.begin(); i != Vconf.end(); i++)
	{
		if ((i->get_Port() == src._port || 0 == i->get_Port()) && (i->get_Host() == "*" || i->get_Host() == src._host))
		{
			if (src._domain == i->get_ServerName() || i->Alias_compare(src._domain))
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

Answer	process_request(Request &src, std::vector<conf> &Vconf)//think this over
{
	std::vector<conf>::iterator iter;
	std::ifstream				file;
	Answer						ret;
	std::string					path;
	std::string					buffer;
	iter = strict_scan(Vconf, src);
	if (iter == Vconf.end())
	{
		iter = non_strict_scan(Vconf, src);
		if (iter == Vconf.end())
			return (Answer(404));
	}
	if (src.isPageADirectory())
	{
		if (!iter->get_listing())
			return (Answer(404));
		std::cout << "Make sure we have a function for directory listing\n Serving a 404 until we add that functionality" << std::endl;
		path = iter->get_ServerRoot() + src._Path + "index.html";
		if (access(path.c_str(), R_OK))
			return (Answer(404));
	}
	else
	{
		src.htmlize();
		path = iter->get_ServerRoot() + src._Path;
		if (access(path.c_str(), R_OK))
			return (Answer(404));
	}
	file.open(path.c_str());
	while (std::getline(file, buffer))
	{
		ret._Body += buffer;
		ret._Body += "\n";//double check if this is necessary
	}
	file.close();
	return (ret);
}