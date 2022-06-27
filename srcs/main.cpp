/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:40:51 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/11 00:13:10 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

int main(int argc, char **argv)
{
	int							status = 0;		//is 0 while the program should run. Giving it a non-zero value will stop the loop
	std::vector<t_socket_info>	socketInitInfo; //array used to create the sockets on the correct port and host
	std::vector<Socket*>		socketList; 	//array storing pointers to memory allocated socket classes
	int							num_sockets;	//the number of sockets initialized

	//initialization:
	std::vector<conf> Vconf;
	init(Vconf, argfile);
	for (std::vector<conf>::iterator i = Vconf.begin(); i != Vconf.end(); i++)
		i->print();
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
	num_sockets = init_sockets(socketInitInfo, socketList); //takes the list of host and port to make sockets on and the list to store created sockets
	if (num_sockets == -1)
		exit(-1); //needs to become cleanup when that function exists
	
	struct pollfd	socketPoll[num_sockets];
	add_sockets_to_poll_list(socketList, socketPoll, num_sockets);

	//loop
	//	-use epoll to monitor all sockets until one has a connection			✓
	//	-parse request from socket
	//	-use config file to find which page corresponds to the request
	//	-append header to content and send to client
	//	-close connection and cleanup
	while (!status)
	{
		reset_socket_poll_list(socketPoll, num_sockets);
		poll(socketPoll, num_sockets, -1); //poll socket list, -1 means infinite timeout, can be set to a positive value for a timeout in ms
		connection_loop(socketList, socketPoll, num_sockets);
	}

	//cleanup
	//	-destroy all of the sockets
	(void)argc;
	(void)argv;
	return (0);
}