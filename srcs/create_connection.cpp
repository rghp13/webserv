/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_connection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:19:02 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/10 20:55:04 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

bool	handle_connection(Socket *socket)
{
	int	connectionFD;

	connectionFD = socket->accept_connection();
	// connection accepted, need to receive info and send answer
}

bool	connection_loop(std::vector<Socket*> socketList, struct pollfd *socketPoll, int sockNumber)
{
	int	socketTemp;

	for (int i = 0; i < sockNumber; i++)
	{
		if (socketPoll[i].revents != 0)
			for (int j = 0; j < sockNumber; j++)
			{
				if (socketList[j]->getFD() == socketPoll[i].fd)
				{
					socketTemp = j;
					break;
				}
			}
	}
	return (true);
}