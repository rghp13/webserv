/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_DELETE.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:39:44 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/12 18:54:15 by dimitriscr       ###   ########.fr       */
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
	full_path = get_ressource_location(location, src._Path);

	if (access(full_path.c_str(), F_OK))
		return (GenerateErrorBody(HTTP_ERR_404, iter)); //file does not exist
	else if (access(full_path.c_str(), W_OK))
		return (GenerateErrorBody(HTTP_ERR_403, iter)); //file doesn't have proper permission
	if (remove(full_path.c_str()) == 0)
	{
		Answer ret;
		ret._Body = src._Path + " has been deleted" + HTTPNL;
		return (ret);
	}
	return (GenerateErrorBody(HTTP_ERR_403, iter));
}