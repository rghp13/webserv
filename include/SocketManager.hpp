/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:59:33 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/24 17:25:51 by dscriabi         ###   ########.fr       */
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
    void    handleRequests(std::vector<conf> Vconf);
    void    cleanConnections( void );
public:
    SocketManager();
    SocketManager(std::vector<t_socket_info> socketInitInfo);
    SocketManager(const SocketManager& srcSocketManager);
	int		cycle(int timeout, std::vector<conf> Vconf);
    ~SocketManager();
};

#endif