/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 04:01:04 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/09 20:38:48 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket()
{
	int	opt = 1;
	_port = 80;
	_host = "*";
	_socketfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (_socketfd == 0)
		throw std::runtime_error("Could not create socket");
	if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		throw std::runtime_error("Can't change socket options");
	_socketinfo.sin_family = AF_INET;
	_socketinfo.sin_addr.s_addr = INADDR_ANY;
	if (_host != "*")
		_socketinfo.sin_addr.s_addr = inet_addr(_host.c_str());
	_socketinfo.sin_port = htons(_port);
}

Socket::Socket(const Socket& src)
{
	int	opt = 1;
	_port = src._port;
	_host = src._host;
	_socketfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (_socketfd == 0)
		throw std::runtime_error("Could not create socket");
	if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		throw std::runtime_error("Can't change socket options");
	_socketinfo.sin_family = AF_INET;
	_socketinfo.sin_addr.s_addr = INADDR_ANY;
	if (_host != "*")
		_socketinfo.sin_addr.s_addr = inet_addr(_host.c_str());
	_socketinfo.sin_port = htons(_port);
}

Socket::Socket(std::string host, int port)
{
	int	opt = 1;
	_port = port;
	_host = host;
	_socketfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (_socketfd == 0)
		throw std::runtime_error("Could not create socket");
	if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		throw std::runtime_error("Can't change socket options");
	_socketinfo.sin_family = AF_INET;
	_socketinfo.sin_addr.s_addr = INADDR_ANY;
	if (_host != "*")
		_socketinfo.sin_addr.s_addr = inet_addr(_host.c_str());
	_socketinfo.sin_port = htons(_port);
}

bool	Socket::bind_socket( void )
{
	if (bind(_socketfd, (struct sockaddr*)&_socketinfo, sizeof(_socketinfo)) < 0) 
	{
		throw std::runtime_error("Couldn't bind socket, port maybe in use");
		return (false);
	}
	return (true);
}

int	Socket::getFD( void ) const
{
	return (_socketfd);
}

int	Socket::accept_connection( void )
{
	int	new_connection;

	new_connection = accept(_socketfd, (struct sockaddr*)&_socketinfo, (socklen_t*)&_socketinfolen);
	if (new_connection < 0)
	{
		throw std::runtime_error("Failed to accept a connection");
		return (-1);
	}
	fcntl(new_connection, F_SETFL, O_NONBLOCK);
	return (new_connection);
}

Socket::~Socket()
{
	shutdown(_socketfd, SHUT_RDWR);
}
