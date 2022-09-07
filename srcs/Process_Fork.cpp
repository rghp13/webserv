/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_Fork.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:35:18 by dscriabi          #+#    #+#             */
/*   Updated: 2022/09/07 15:02:52 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

Answer	fork_request(Request request, std::vector<conf> Vconf)
{
	Answer	retval;

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
	if (request._host.size() > 4096) //URI is too long
	{
		retval.SetStatus(HTTP_ERR_414);
		return (retval);
	}
	if (request._Method == "GET")
	{
		//commit GET processing
		retval = process_get(request, Vconf);
		return (retval);
	}
	if (request._Method == "POST")
	{
		//commit POST processing
		return (retval);
	}
	if (request._Method == "DELETE")
	{
		//commit DELETE processing
		return (retval);
	}
	retval.SetStatus(HTTP_ERR_501);
	return (retval);
}