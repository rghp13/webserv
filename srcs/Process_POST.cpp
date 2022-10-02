/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_POST.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:25:28 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/02 14:57:58 by rponsonn         ###   ########.fr       */
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

//since no one can explain how post works i'll scrape the data
Answer process_post(Request &src, std::vector<conf>::iterator iter, location location)
{
	std::string full_path;
	std::string content_type;

	Answer ret(200);
	if (!src.key_exists("Content-Length:"))
		return (Answer(411));//length required
	else
	{
		std::string len = src.get_keyval("Content-Length:").value;
		if (iter->get_MaxSize() < static_cast<unsigned long int>(std::atol(len.c_str())))
			return (Answer(413));
	}
	if (src.key_exists("Content-Type:"))
	{
		content_type = src.get_keyval("Content-Type:").value;
	}
	else
		content_type = "text/plain";
	if (content_type == "text/plain")
		plain_post(src, iter, location);
	else if (content_type == "application/x-www-form-urlencoded")
		form_post(src, iter, location);
	else if (content_type == "multipart/form-data")
		multi_post(src, iter, location);
	else
	{
		std::cerr << "content-type mismatch" << std::endl;
		plain_post(src, iter, location);
	}
	
}
void	plain_post(Request &src, std::vector<conf>::iterator iter, location location)
{
	time_t hold = time(0);
	std::string filename = "File" + hold;
}