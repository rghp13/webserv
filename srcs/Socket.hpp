/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 03:59:50 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/09 19:46:47 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
 #define SOCKET_HPP
#include "../include/webserv.hpp"

class Socket
{
private:
	int					_port;
	std::string			_host;
	int					_socketfd;
	struct sockaddr_in	_socketinfo;
	int					_socketinfolen;
public:
	Socket();
	Socket(const Socket& src);
	Socket(std::string host, int port);
	bool		bind_socket( void );
	int		getFD( void ) const;
	int		accept_connection( void );
	~Socket();
};

#endif