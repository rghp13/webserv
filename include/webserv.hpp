/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:41:19 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/12 18:56:33 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
 #define WEBSERV_HPP

#include <string> //string functions
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

#include <stdlib.h>//apparently exit requires stdlib.h
#include <unistd.h> //read, write, close, etc...
#include <dirent.h> //get list of files in directory
#include <fcntl.h>
#include <exception>
#include <vector>

#include <netinet/in.h> //variable types that can hold ip addresses
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h> //socket stuff
#include <sys/select.h>//select
#include <sys/epoll.h>//epoll
#include <arpa/inet.h>//htons htonl ntohs ntohl
#include <poll.h>//poll

#define GET 0b1
#define POST 0b10
#define DELETE 0b100
#define PORT 80
#define HTTP_VERS "HTTP/1.1"
#define HTTPNL "\r\n"
#define	HTTP_ERR_301 301, "Moved Permanently"
#define	HTTP_ERR_302 302, "Found"
#define HTTP_ERR_303 303, "See Other"
#define HTTP_ERR_307 307, "Temporary Redirect"
#define HTTP_ERR_308 308, "Permanent Redirect"
#define HTTP_ERR_400 400, "Bad Request"
#define HTTP_ERR_403 403, "Forbidden"
#define HTTP_ERR_404 404, "Not Found"
#define HTTP_ERR_405 405, "Method Not Allowed"
#define	HTTP_ERR_408 408, "Request Timeout"
#define HTTP_ERR_414 414, "URI Too Long"
#define HTTP_ERR_418 418, "I'm a teapot"
#define	HTTP_ERR_500 500, "Internal Server Error"
#define HTTP_ERR_501 501, "Not Implemented"
#define HTTP_ERR_505 505, "HTTP Version Not Supported"
class conf;
class Socket;
class Connection;
class Answer;
class Request;
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
		( std::ostringstream() << std::dec << x ) ).str()
#define KB(x) (x * 1024UL)
#define MB(x) (x * (1024UL * 1024UL))
#define GB(x) (x * (1024UL * 1024UL * 1024UL))

#define MAXQUEUESIZE 3
//research FD_SET, FD_CLR, FD_ISSET, FD_ZERO 

typedef	struct	s_socket_info
{
	std::string		host;
	unsigned int	port;
}				t_socket_info;

typedef	struct	s_header_argument
{
	std::string		key;
	std::string		value;
}				t_header_argument;

typedef struct	s_redirect
{
	int code;
	std::string value;
}				t_redirect;

#include "conf.hpp"
#include "Socket.hpp"
#include "Request.hpp"
#include "Answer.hpp"
#include "Connection.hpp"
#include "SocketManager.hpp"

int		init(std::vector<conf> &Vconf, std::ifstream &file);
bool	boot_check(int argc, char **argv, std::ifstream &argfile);
void	RemoveWordString(std::string &line, const std::string &word);
int		init_sockets(std::vector<t_socket_info> &socketInfos, std::vector<Socket*> &SocketRefLists);
void	add_sockets_to_poll_list(std::vector<Socket*> socketList, struct pollfd	*socketPoll, int sockNumber);
void	reset_socket_poll_list(struct pollfd *socketPoll, int sockNumber);
bool	connection_loop(std::vector<Socket*> socketList, struct pollfd *socketPoll, int sockNumber);
int		fill_socket_vector(std::vector<t_socket_info> &socketInitInfo, std::vector<conf> &Vconf);
bool	check_duplicate_socket(std::vector<t_socket_info> &socketInitInfo);
std::string	generateDirectoryPage(std::string dirPath, std::string docroot);
Answer	fork_request(Request request, std::vector<conf> Vconf);
//Process_get.cpp
Answer	process_get(Request &src, std::vector<conf>::iterator iter);
std::vector<conf>::iterator	strict_scan(std::vector<conf> &Vconf, Request &src);
std::vector<conf>::iterator	non_strict_scan(std::vector<conf> &Vconf, Request &src);
//Process_delete.cpp
Answer	process_delete(Request &src, std::vector<conf>::iterator iter);
//Process_post.cpp
Answer	process_post(Request &src, std::vector<conf>::iterator iter);
//Utils.cpp
bool	isdir(std::string input);
#endif