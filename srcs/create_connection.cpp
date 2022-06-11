/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_connection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:19:02 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/11 02:31:43 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

bool	receive_and_send_answer(int fd)
{
	int		readret;
	char	buffer[1024] = {0};

	readret = read(fd, buffer, 1024); //read data like in an open file
	if (readret < 0)
		return (false);
	std::cout << buffer << std::endl;
	send(fd, "received", 8, 0); //send data to the client
	return (true);
}

bool	handle_connection(Socket *socket)
{
	int				connectionFD;
	struct pollfd	socketPoll;

	connectionFD = socket->accept_connection(); //accept connection
	if (connectionFD == -1)
		return (false);

	socketPoll.fd = connectionFD;
	socketPoll.events = POLLIN;
	socketPoll.revents = 0;
	poll(&socketPoll, 1, -1); //wait for client to be ready to send

	receive_and_send_answer(connectionFD);

	close(connectionFD);
	return (true);
}

bool	connection_loop(std::vector<Socket*> socketList, struct pollfd *socketPoll, int sockNumber)
{
	for (int i = 0; i < sockNumber; i++)
	{
		if (socketPoll[i].revents != 0)
		{
			for (int j = 0; j < sockNumber; j++)
			{
				if (socketList[j]->getFD() == socketPoll[i].fd)
				{
					std::cout << "handling socket" << socketList[j]->getFD() << std::endl;
					handle_connection(socketList[j]);
					break;
				}
			}
		}
	}
	return (true);
}