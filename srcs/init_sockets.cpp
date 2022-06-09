/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sockets.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:29:07 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/09 23:47:35 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"
#include "Socket.hpp"

int	init_sockets(std::vector<t_socket_info> &socketInfos, std::vector<Socket> &SocketRefLists)
{
	try
	{
		for(std::vector<t_socket_info>::size_type i = 0; i != socketInfos.size(); i++)
		{
			SocketRefLists.push_back(Socket(socketInfos[i].host, socketInfos[i].port));
			SocketRefLists.back().bind_socket();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (-1);
	}
	return (SocketRefLists.size());
}