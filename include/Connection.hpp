/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:29:55 by dscriabi          #+#    #+#             */
/*   Updated: 2022/09/05 16:03:39 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_HPP
 #define CONNECTION_HPP
#include "../include/webserv.hpp"

class Connection
{
private:
	int		_FD;
	bool	_KeepAlive;
	time_t	_LastActivity;
public:
	Connection();
	Connection(int NewFD);
	Connection(const Connection& src);
	int		GetConnectionFD( void ) const;
	bool	ShouldDestroy( void ) const;
	bool	GetKeepAlive( void ) const;
	bool	SetKeepAlive( bool newval );
	std::string	GetNewestClientRequest( void );
	bool	SendAnswer(std::string Answer);
	~Connection();

};

#endif