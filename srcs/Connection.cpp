/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:55:23 by dscriabi          #+#    #+#             */
/*   Updated: 2022/09/09 14:08:28 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"

Connection::Connection()
{
	_FD = -1;
	_KeepAlive = true;
	_LastActivity = time(NULL);
}

Connection::Connection(int NewFD, t_socket_info sockinfo)
{
	_FD = NewFD;
	_port = sockinfo.port;
	_host = sockinfo.host;
	_KeepAlive = true;
	_LastActivity = time(NULL);
}

Connection::Connection(const Connection& src)
{
	_FD = src._FD;
	_port = src._port;
	_host = src._host;
	_KeepAlive = src._KeepAlive;
	_LastActivity = src._LastActivity;
}

int		Connection::GetConnectionFD( void ) const
{
	return (_FD);
}

int		Connection::GetPort( void ) const
{
	return (_port);
}

std::string	Connection::GetHost( void ) const
{
	return (_host);
}

bool	Connection::ShouldDestroy ( void ) const
{
	if (_KeepAlive == false)
		return (true);
	if (difftime(time(NULL), _LastActivity) > 10.0f)
		return (true);
	return (false);
}

bool	Connection::GetKeepAlive( void ) const
{
	return (_KeepAlive);
}

bool	Connection::SetKeepAlive( bool newval )
{
	_KeepAlive = newval;
	return (_KeepAlive);
}

bool	Connection::IsRequestFull( std::string request) const
{
	size_t	double_end_line_pos;

	double_end_line_pos = request.find("\r\n\r\n");
	if (double_end_line_pos == std::string::npos)
		return (false);
	if (request.find("Content-Length") != std::string::npos && request.find("\r\n", double_end_line_pos + 4) == std::string::npos)
		return (false);
	return (true);
}

std::string	Connection::GetNewestClientRequest( void )
{
	//read from the connection to get client request
	int			readret;
	char		buffer[1025] = {0};
	std::string	retstr;
	time_t		start = time(NULL);

	readret = 1024;
	retstr = "";
	while (readret > 0 || (!this->IsRequestFull(retstr) && difftime(time(NULL), start) < 1.0f))
	{
		readret = read(_FD, buffer, 1024);
		if (readret > 0)
		{
			buffer[readret] = '\0';
			retstr.append(buffer);
			start = time(NULL);
		}
	}
	// std::cout << "_________________________" << std::endl;
	// std::cout << retstr;
	// std::cout << "_________________________" << std::endl;
	return (retstr);
}

bool		Connection::SendAnswer(std::string answerstr)
{
	//send an answer to the client, return success status and update _LastActivity
	send(_FD, answerstr.c_str(), answerstr.length(), 0);
	_LastActivity = time(NULL);
	std::cout << "Sent Answer" << std::endl;
	return (true);
}

Connection::~Connection()
{
	close (_FD);
}
