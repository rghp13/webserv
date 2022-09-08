/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:29:55 by dscriabi          #+#    #+#             */
/*   Updated: 2022/09/08 16:55:55 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_HPP
 #define CONNECTION_HPP
#include "../include/webserv.hpp"

class Connection
{
private:
	int			_FD;
	int			_port;
	std::string	_host;
	bool		_KeepAlive;
	time_t		_LastActivity;
public:
	Connection();
	Connection(int NewFD, t_socket_info sockinfo);
	Connection(const Connection& src);
	int			GetConnectionFD( void ) const;
	int			GetPort( void ) const;
	std::string	GetHost( void ) const;
	bool		ShouldDestroy( void ) const;
	bool		GetKeepAlive( void ) const;
	bool		SetKeepAlive( bool newval );
	bool		IsRequestFull( std::string request ) const;
	std::string	GetNewestClientRequest( void );
	bool		SendAnswer(std::string answerstr);
	~Connection();

};

#endif