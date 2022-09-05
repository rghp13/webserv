/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:55:23 by dscriabi          #+#    #+#             */
/*   Updated: 2022/09/05 16:35:08 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"

Connection::Connection()
{
	_FD = -1;
	_KeepAlive = true;
	_LastActivity = time(NULL);
}

Connection::Connection(int NewFD)
{
	_FD = NewFD;
	_KeepAlive = true;
	_LastActivity = time(NULL);
}

Connection::Connection(const Connection& src)
{
	_FD = src._FD;
	_KeepAlive = src._KeepAlive;
	_LastActivity = src._LastActivity;
}

int		Connection::GetConnectionFD( void ) const
{
	return (_FD);
}

bool	Connection::ShouldDestroy ( void ) const
{
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

std::string	Connection::GetNewestClientRequest( void )
{
	//read from the connection to get client request
	int			readret;
	char		buffer[1024] = {0};
	std::string	retstr;

	readret = 1024;
	retstr = "";
	while (readret == 1024)
	{
		readret = read(_FD, buffer, 1024);
		retstr.append(buffer);
	}
	return (retstr);
}

bool		Connection::SendAnswer(std::string Answer)
{
	//send an answer to the client, return success status and update _LastActivity
	send(_FD, Answer.c_str(), Answer.length(), 0);
	_LastActivity = time(NULL);
	return (true);
}

Connection::~Connection()
{
}
