/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:40:51 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/10 02:24:36 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

int main(int argc, char **argv)
{
	std::vector<t_socket_info>	socketInitInfo;
	std::vector<Socket*>			socketList;
	int							num_sockets;

	//initialization:
	// -check config file
	// -load config file
	// -get a list of all prots that nned websockets
	//===========temp init=============
	t_socket_info	tempinit;
	tempinit.host = "*";
	tempinit.port = 8081;
	socketInitInfo.push_back(tempinit);
	tempinit.host = "*";
	tempinit.port = 8082;
	socketInitInfo.push_back(tempinit);
	tempinit.host = "127.0.0.1";
	tempinit.port = 8083;
	socketInitInfo.push_back(tempinit);
	//================================

	//start websockets on each of the ports
	num_sockets = init_sockets(socketInitInfo, socketList);
	if (num_sockets == -1)
		exit(-1); //needs to become cleanup when that function exists

	//loop
	//	-use epoll to monitor all sockets until one has a connection
	//	-parse request from socket
	//	-use config file to find which page corresponds to the request
	//	-append header to content and send to client
	//	-close connection and cleanup

	while (1)
	{
		sleep(100);
	}
	//cleanup
	//	-destroy all of the sockets
	(void)argc;
	(void)argv;
	return (0);
}