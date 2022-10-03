/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_PUT.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 01:52:15 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/10/03 03:10:54 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

//Let it be noted here that PUT is not required for the project and that everyting i do here is just to see the automatic tester give me a 100%, I really hate myself

Answer process_put(Request &src, std::vector<conf>::iterator iter, location location)
{
	std::string		path;
	size_t 			size;
	std::ofstream	file;
	Answer			retval;

	(void)iter;
	size = location._path.size();
	if (location._path.at(size - 1))
		size -= 1;
	path = location._uploaddir;
	path += src._Path.substr(size);
	if (is_ressource_directory(path))
	{
		retval.SetStatus(HTTP_ERR_404);
		return (retval);//fail, the proper response turns out to be 404
	}
	if (access(path.c_str(), F_OK))
	{
		//file does not yet exist
		file.open(path.c_str());
		file << src._Body;
		file.close();
		retval.SetStatus(HTTP_ERR_201);
		return (retval);
	}
	//file does exist
	if (access(path.c_str(), W_OK))
	{
		retval.SetStatus(HTTP_ERR_404);
		return (retval); //file already exists and cant be written to
	}
	//file exists and can be witten to
	std::cout << "Appended " << path << std::endl;
	file.open(path.c_str(), std::ofstream::trunc);
	file << src._Body;
	file.close();
	retval._Body = "Overwrote previous data";
	retval._Body += HTTPNL;
	retval.SetBodyLen();
	return (retval);
}