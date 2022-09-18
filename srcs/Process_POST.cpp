/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_POST.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:25:28 by rponsonn          #+#    #+#             */
/*   Updated: 2022/09/17 17:10:28 by rponsonn         ###   ########.fr       */
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
//sample
// POST /test HTTP/1.1
// Host: foo.example
// Content-Type: multipart/form-data;boundary="boundary"

// --boundary
// Content-Disposition: form-data; name="field1"

// value1
// --boundary
// Content-Disposition: form-data; name="field2"; filename="example.txt"

// value2
// --boundary--
//find a way to store all the keywords, then pull data from body
Answer process_post(Request &src, std::vector<conf>::iterator iter)
{
	std::string full_path;
	
	Answer ret(200);
	if (!src.key_exists("Content-Length:"))
		return (Answer(411));//length required
	t_header_argument tmp = src.get_keyval("Content-Length:");
	//if (iter->get_MaxSize() < static_cast<unsigned long int>(std::atol(tmp.value.c_str())))
	//	return (Answer(413));
	
}