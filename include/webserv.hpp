/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:41:19 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/27 21:31:44 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
 #define WEBSERV_HPP

#include <string> //string functions
#include <fstream>
#include <iostream>

#include <stdlib.h>//apparently exit requires stdlib.h
#include <unistd.h> //read, write, close, etc...
#include <fcntl.h>
#include <exception>
#include <vector>

#include <netinet/in.h> //variable types that can hold ip addresses
#include <sys/types.h>
#include <sys/socket.h> //socket stuff
#include <sys/select.h>//select
#include <sys/epoll.h>//epoll
#include <arpa/inet.h>//htons htonl ntohs ntohl
#include <poll.h>//poll

#include "conf.hpp"
#define PORT 80
class conf;
#include "Socket.hpp"
#include "Request.hpp"
#include "Answer.hpp"

#define MAXQUEUESIZE 3
//research FD_SET, FD_CLR, FD_ISSET, FD_ZERO 

class Socket;

typedef	struct	s_socket_info
{
	std::string		host;
	unsigned int	port;
}				t_socket_info;

int		init(std::vector<conf> &Vconf, std::ifstream &file);
bool	boot_check(int argc, char **argv, std::ifstream &argfile);
void	RemoveWordString(std::string &line, const std::string &word);
int		init_sockets(std::vector<t_socket_info> &socketInfos, std::vector<Socket*> &SocketRefLists);
void	add_sockets_to_poll_list(std::vector<Socket*> socketList, struct pollfd	*socketPoll, int sockNumber);
void	reset_socket_poll_list(struct pollfd *socketPoll, int sockNumber);
bool	connection_loop(std::vector<Socket*> socketList, struct pollfd *socketPoll, int sockNumber);

#endif