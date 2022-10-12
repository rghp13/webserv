/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_POST.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:25:28 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/12 18:52:53 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"
//important keys Content-Type and Content-Length
/*
**Annotation of existing resources
**Posting a message to a bulletin board, newsgroup, mailing list, or similar group of articles;
**Adding a new user through a signup modal;
**Providing a block of data, such as the result of submitting a form, to a data-handling process;
**Extending a database through an append operation.
*/
//The type of body in the post is determined by the header key "Content-Type"

//application/x-www-form-urlencoded is done with key-value pairs.
//'='separates the key and value. '&' separates variables

//multipart/form-data is sent as blocks of data with boundary delimiter that is set in 'Content-Disposition' header
//

//text/plain

//since absolutely no one can explain how post works i'm making it up as I go
//if you claim i did something wrong you'll have to explain how post works
Answer process_post(Request &src, std::vector<conf>::iterator iter, location location)
{
	std::string content_type;

	if (src._Path.substr(src._Path.size() - location._cgi.first.size(), location._cgi.first.size()) == location._cgi.first)
	{
		//run cgi
		Answer		ret;
		std::string	temp;
		CGIManager	cgi(src, *iter, location);
		temp = cgi.runCGI();
		if (temp == "Error Status 500")
			return (GenerateErrorBody(HTTP_ERR_500, iter));
		ret._Body = temp.substr(temp.find("\r\r") + 2);
		//ret._Body += HTTPNL;
		ret.SetBodyLen();
		return (ret);
	}
	if (!src.key_exists("Content-Length:"))
		return (GenerateErrorBody(HTTP_ERR_411, iter));//length required
		//return(GenerateErrorAnswer(HTTP_ERR_411, iter));
	else
	{
		std::string len = src.get_keyval("Content-Length:").value;
		if (iter->get_MaxSize() < static_cast<unsigned long int>(std::atol(len.c_str())))
			return (GenerateErrorBody(HTTP_ERR_413, iter));
	}
	if (src.key_exists("Content-Type:"))
	{
		content_type = src.get_keyval("Content-Type:").value;
	}
	if (content_type == "text/plain")
		return (plain_post(src, location, iter));
	/*else if (content_type == "application/x-www-form-urlencoded")
		;//form_post(src, iter, location);
	else if (content_type == "multipart/form-data")
		;//multi_post(src, iter, location);*/
	else
	{
		std::cerr << "content-type mismatch" << std::endl;
		return(GenerateErrorBody(HTTP_ERR_415, iter));
	}
}
Answer	plain_post(Request &src, location location, std::vector<conf>::iterator iter)
{
	//do nothing special, just dump it into a file;
	std::string filename;
	std::ofstream file;

	//first create a filename
	filename = newfilename(location);
	file.open(filename.c_str());
	if (file.fail())
		return (GenerateErrorBody(HTTP_ERR_500, iter));
	file << src._Body;
	if (file.fail())
		return (GenerateErrorBody(HTTP_ERR_500, iter));
	file.close();
	return (GenerateErrorBody(HTTP_ERR_201, iter));
	
}
std::string	newfilename(location location)//creates semi-random filename
{
	std::string	filename = "file_" + SSTR(time(0));
	std::string	fileroot;
	std::string	ret;
	int			fileno = 0;
	if (location._uploaddir.empty())
	{
		fileroot = DEF_UPL_DIR;
		//if (access(fileroot.c_str(), W_OK))
		//	return (Answer(500));see how it handles without this check
	}
	else
		fileroot = location._uploaddir;
	while (true)
	{
		ret = fileroot + filename + SSTR(fileno);
		if (access(ret.c_str(), F_OK))//file doesn't exist
			return (ret);
		else
			++fileno;
	}
}