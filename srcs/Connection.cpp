/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:55:23 by dscriabi          #+#    #+#             */
/*   Updated: 2022/10/04 18:41:23 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

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
	if (difftime(time(NULL), _LastActivity) > KEEP_ALIVE_TIME)
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
	if (request.find("Transfer-Encoding: chunked") != std::string::npos && request.find("0\r\n\r\n", double_end_line_pos + 4) == std::string::npos) //this needs polish
		return (false);
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
	char		buffer[RECV_SIZE] = {0};
	std::string	temp;

	// readret = RECV_SIZE;
	// retstr = "";
	// while (readret > 0 || (!this->IsRequestFull(retstr) && difftime(time(NULL), start) < 10.0f))
	// {
	// 	readret = read(_FD, buffer, RECV_SIZE);
	// 	if (readret > 0)
	// 	{
	// 		buffer[readret] = '\0';
	// 		retstr.append(buffer);
	// 		start = time(NULL);
	// 	}
	// }
	// retstr = dechunk(retstr);
	// if (retstr.find("Connection: close") != std::string::npos)
	// 	_KeepAlive = false;
	// return (retstr);
	readret = read(_FD, buffer, RECV_SIZE);
	if (readret <= 0 )
	{
		_KeepAlive = false;
		return ("");
	}
	std::cout << "Received " << readret << " bytes" << std::endl;
	_LastActivity = time(NULL);
	buffer[readret] = '\0';
	_Requesthold.append(buffer);
	if (this->IsRequestFull(_Requesthold))
	{
		if (_Requesthold.find("Connection: close") != std::string::npos)
			_KeepAlive = false;
		temp = dechunk(_Requesthold);
		_Requesthold = "";
		std::cout << "returned" << std::endl;
		return (temp);
	}
	return ("");
}

bool		Connection::SendAnswer(std::string answerstr)
{
	//send an answer to the client, return success status and update _LastActivity
	send(_FD, answerstr.c_str(), answerstr.length(), 0);
	_LastActivity = time(NULL);
	return (true);
}

Connection::~Connection()
{
	close (_FD);
	std::cout << "closed a socket" << std::endl;
}
