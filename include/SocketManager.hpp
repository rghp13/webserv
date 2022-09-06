/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:59:33 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/06 14:53:35 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETMANAGER_HPP
 #define SOCKETMANAGER_HPP
#include "webserv.hpp"

class SocketManager
{
private:
    std::vector<Socket*>		_SocketList;
	std::vector<Connection*>	_ActiveConnectionList;
	int							_PollListSize;
	struct pollfd				*_PollList;

	void	fillPollList( void );
    void    createNewConnections( void );
    void    handleRequests( void );
    void    cleanConnections( void );
public:
    SocketManager();
    SocketManager(std::vector<t_socket_info> socketInitInfo);
    SocketManager(const SocketManager& srcSocketManager);
	int		cycle(int timeout);
    ~SocketManager();
};

#endif