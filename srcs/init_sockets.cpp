/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sockets.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:29:07 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/10 02:13:52 by dimitriscr       ###   ########.fr       */
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
			socketList.push_back( new Socket(socketInfos[i].host, socketInfos[i].port));
			socketList.back()->bind_socket();
			socketList.back()->start_listening(3);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (-1);
	}
	return (socketList.size());
}