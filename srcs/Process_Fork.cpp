/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_Fork.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:35:18 by dscriabi          #+#    #+#             */
/*   Updated: 2022/09/09 18:26:02 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

Answer	fork_request(Request request, std::vector<conf> Vconf)
{
	Answer						retval;
	std::vector<conf>::iterator	current_conf;

	if (request._malformed) //Malformed Request
	{
		retval.SetStatus(HTTP_ERR_400);
		std::cout << "Error 400 on Request" << std::endl;
		return (retval);
	}
	if (request._Version != HTTP_VERS) //Incorrect HTTP Version
	{
		retval.SetStatus(HTTP_ERR_505);
		std::cout << "Error 505 on Request, http request was: " << request._Version << std::endl;
		return (retval);
	}
	if (request._Path.size() > 4096) //URI is too long
	{
		retval.SetStatus(HTTP_ERR_414);
		std::cout << "Error 414 on Request" << std::endl;
		return (retval);
	}

	//Get the config that matches the socket this request came from
	current_conf = strict_scan(Vconf, request);
	if (current_conf == Vconf.end())
	{
		current_conf = non_strict_scan(Vconf, request);
		if (current_conf == Vconf.end())
		{
			retval.SetStatus(HTTP_ERR_500);
			return (retval);
		}
	}
	//

	if (current_conf->get_redirect().code != 0)
	{
		int	code = current_conf->get_redirect().code;
		t_header_argument	redirect;
		if (code > 299 && code < 400)
		{
			if (code == 301)
				retval.SetStatus(HTTP_ERR_301);
			else if (code == 302)
				retval.SetStatus(HTTP_ERR_302);
			else if (code == 303)
				retval.SetStatus(HTTP_ERR_303);
			else if (code == 307)
				retval.SetStatus(HTTP_ERR_307);
			else if (code == 308)
				retval.SetStatus(HTTP_ERR_308);
			redirect.key = "Location:";
			redirect.value = current_conf->get_redirect().value;
			retval.AddArgument(redirect);
			return (retval);
		}
		retval.SetStatus(code, current_conf->get_redirect().value);
		retval.GenerateErrorBody();
		return (retval);
	}
	
	if (request._Method == "GET")
	{
		//commit GET processing
		if ((current_conf->get_Method()&GET) != GET)
		{
			retval.SetStatus(HTTP_ERR_405);
			return (retval);
		}
		std::cout << "accepted as GET" << std::endl;
		retval = process_get(request, current_conf);
		return (retval);
	}
	if (request._Method == "POST")
	{
		//commit POST processing
		if ((current_conf->get_Method()&POST) != POST)
		{
			retval.SetStatus(HTTP_ERR_405);
			return (retval);
		}
		return (retval);
	}
	if (request._Method == "DELETE")
	{
		//commit DELETE processing
		if ((current_conf->get_Method()&DELETE) != DELETE)
		{
			retval.SetStatus(HTTP_ERR_405);
			return (retval);
		}
		std::cout << "accepted as DELETE" << std::endl;
		retval = process_delete(request, current_conf);
		return (retval);
	}
	retval.SetStatus(HTTP_ERR_501);
	return (retval);
}