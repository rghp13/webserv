/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:40:51 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/05/31 14:11:36 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

int main(int argc, char **argv)
{
	int					socketfd; //holds the fd of the socket
	struct sockaddr_in	address;  //holds data about the socket binding
	int 				addresslen = sizeof(address);
	std::string			message = "Test message"; //message to display in the web browser

	if (argc > 1)
		message = argv[1];
	
	//create the socket
	socketfd = socket(AF_INET, SOCK_STREAM, 0); 
	//first argument is AF_LOCAL for local processes, AF_INET for ipv4 and AF_INET6 for ipv6
	//second argument is SOCK_STREAM for tcp connection and SOCK_DGRAM for udp connection
	//last argument is the protocol, 0 is for ip
	//returns 0 if error
	if (socketfd == 0)
	{
		std::cout << "Socket creation failed" << std::endl;
		exit(-1);
	}

	//set socket binding options
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT); //port to bind too. Note: ports under 1024 require sudo on UNIX systems

	//bind the socket
	if (bind(socketfd, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		std::cout << "Failed to bind socket to port " << PORT << std::endl;
		exit(-2);
	}

	//set up the socket to allow connections
	if (listen(socketfd, 3) < 0) //listen sets the socket for connections, the second arguments is the number of connection that can be queued on the socket
	{
		std::cout << "Failed to listen on socket" << std::endl;
		exit(-3);
	}

	int		clientfd;
	int		readret;
	char	buffer[1024] = {0};
	//accept a connection
	clientfd = accept(socketfd, (struct sockaddr*)&address, (socklen_t*)&addresslen); //waits for a connection and accepts it
	if (clientfd < 0)
	{
		std::cout << "Connection couldn't be accepted" << std::endl;
		exit(-4);
	}
	readret = read(clientfd, buffer, 1024); //read data like in an open file
	if (readret < 0)
	{
		std::cout << "Can't read from socket" << std::endl;
		exit(-5);
	}
	std::cout << buffer << std::endl;
	send(clientfd, message.c_str(), message.length(), 0); //send data to the client

	//disconnect client
	close(clientfd);
	//close the socket
	shutdown(socketfd, SHUT_RDWR);
	return (0);
}