/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_DELETE.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:39:44 by rponsonn          #+#    #+#             */
/*   Updated: 2022/09/08 17:40:45 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"
//delete request may have a body
//may get a body response
//
Answer	process_delete(Request &src, std::vector<conf> &Vconf)
{
	std::vector<conf>::iterator iter;
	std::string full_path;
	iter = strict_scan(Vconf, src);
	if (iter == Vconf.end())
	{
		iter = non_strict_scan(Vconf, src);
		if (iter == Vconf.end())
			return (Answer(404));
	}
	//use isdir()instead
	full_path = iter->get_DocumentRoot() + src._Path;

	if (access(full_path.c_str(), F_OK))
	{
		//file does not exist
		return (Answer(404));
	}
	else if (access(full_path.c_str(), W_OK))
	{
		//file doesn't have proper permission
		return (Answer(403));
	}
	if (remove(full_path.c_str()) == 0)
	{
		Answer ret;
		ret._Body = src._Path + " has been deleted" + HTTPNL;
		return (ret);
	}
	return (Answer(403));	
}