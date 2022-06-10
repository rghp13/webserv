/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_poll.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:16:41 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/10 19:26:03 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

void	add_sockets_to_poll_list(std::vector<Socket*> socketList, struct pollfd *socketPoll, int sockNumber)
{
	for (int i = 0; i < sockNumber; i++)
	{
		socketPoll[i].fd = socketList.at(i)->getFD();
		socketPoll[i].events = POLLIN;
		socketPoll[i].revents = 0;
	}	
}

void	reset_socket_poll_list(struct pollfd *socketPoll, int sockNumber)
{
	for (int i = 0; i < sockNumber; i++)
	{
		socketPoll[i].revents = 0;
	}
}