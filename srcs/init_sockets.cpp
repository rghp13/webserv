/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sockets.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:29:07 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/10 02:25:00 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"
#include "Socket.hpp"

int	init_sockets(std::vector<t_socket_info> &socketInfos, std::vector<Socket*> &socketList)
{
	try
	{
		for(std::vector<t_socket_info>::size_type i = 0; i != socketInfos.size(); i++)
		{
			socketList.push_back( new Socket(socketInfos[i].host, socketInfos[i].port));		//create the socket and store it's pointer in a vector
			socketList.back()->bind_socket();													//bind the socket to the port
			socketList.back()->start_listening(MAXQUEUESIZE);									//start the socket in listen (receive) mode with a queue size of 
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		for (std::vector<Socket*>::size_type i = 0; i < socketList.size(); i++)					//delete all the sockets if there is an error somewhere
		{
			delete socketList[i];
		}
		return (-1);
	}
	return (socketList.size());
}