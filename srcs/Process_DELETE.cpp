/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_DELETE.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:39:44 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/02 14:33:26 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"
//delete request may have a body
//may get a body response
//
Answer	process_delete(Request &src, std::vector<conf>::iterator iter, location location)
{
	std::string full_path;

	//use is_ressource_directory() to check if its a folder, might need default file substitution
	(void)iter; //needed for default error pages
	full_path = get_ressource_location(location, src._Path);

	if (access(full_path.c_str(), F_OK))
		return (Answer(404)); //file does not exist
	else if (access(full_path.c_str(), W_OK))
		return (Answer(403)); //file doesn't have proper permission
	if (remove(full_path.c_str()) == 0)
	{
		Answer ret;
		ret._Body = src._Path + " has been deleted" + HTTPNL;
		return (ret);
	}
	return (Answer(403));	
}