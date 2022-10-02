/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_Fork.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:35:18 by dscriabi          #+#    #+#             */
/*   Updated: 2022/10/02 14:15:52 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

location	locationForRequest(Request request, std::vector<conf>::iterator config) //this doesn't work anymore
{
	int			foundlength = 0;
	location	retloc;

	for (size_t i = 0; i < config->get_location().size(); i++)
	{
		//if (config->get_location().at(i)._path.size() - 1 <= request._Path.size() && config->get_location().at(i)._path.compare(0, config->get_location().at(i)._path.size() - 1, request._Path) == 0)
		if (config->get_location().at(i)._path.substr(0, config->get_location().at(i)._path.size() - 1) == request._Path.substr(0, config->get_location().at(i)._path.size() - 1))
		{
			if (config->get_location().at(i)._path.size() - 1 == request._Path.size() || request._Path.at(config->get_location().at(i)._path.size() - 1) == '/')
			{
				if ((int)config->get_location().at(i)._path.size() > foundlength)
				{
					retloc = config->get_location().at(i);
					foundlength = config->get_location().at(i)._path.size();
				}
			}
		}
	}
	if (foundlength == 0)
		retloc = get_root_loc(config);
	std::cout << "Chose location: " << retloc._path << std::endl;
	return (retloc);
}

Answer	fork_request(Request request, std::vector<conf> Vconf)
{
	Answer						retval;
	location					current_location;
	std::vector<conf>::iterator	current_conf;

	if (request._malformed) //Malformed Request
	{
		retval.SetStatus(HTTP_ERR_400);
		return (retval);
	}
	if (request._Version != HTTP_VERS) //Incorrect HTTP Version
	{
		retval.SetStatus(HTTP_ERR_505);
		return (retval);
	}
	if (request._Path.size() > 4096) //URI is too long
	{
		retval.SetStatus(HTTP_ERR_414);
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
	current_location = locationForRequest(request, current_conf);

	if (current_location._redirection.first != 0)
	{
		int	code = current_location._redirection.first;
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
			redirect.value = current_location._redirection.second;
			retval.AddArgument(redirect);
			return (retval);
		}
		retval.SetStatus(code, current_location._redirection.second);
		retval.GenerateErrorBody();
		return (retval);
	}
	
	if (request._Method == "GET")
	{
		//commit GET processing
		if ((current_location._methods&GET) != GET)
		{
			retval.SetStatus(HTTP_ERR_405);
			return (retval);
		}
		retval = process_get(request, current_conf, current_location);
		return (retval);
	}
	if (request._Method == "HEAD")
	{
		//commit HEAD processing
		if ((current_location._methods&HEAD) != HEAD)
		{
			retval.SetStatus(HTTP_ERR_405);
			retval._Body = "";
			return (retval);
		}
		retval = process_get(request, current_conf, current_location);
		retval._Body = "";
		return (retval);
	}
	if (request._Method == "POST")
	{
		//commit POST processing
		if ((current_location._methods&POST) != POST)
		{
			retval.SetStatus(HTTP_ERR_405);
			return (retval);
		}
		//post here
		return (retval);
	}
	if (request._Method == "DELETE")
	{
		//commit DELETE processing
		if ((current_location._methods&DELETE) != DELETE)
		{
			retval.SetStatus(HTTP_ERR_405);
			return (retval);
		}
		retval = process_delete(request, current_conf, current_location);
		return (retval);
	}
	retval.SetStatus(HTTP_ERR_501);
	return (retval);
}