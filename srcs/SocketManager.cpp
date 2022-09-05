/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:12:52 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/05 18:23:49 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/SocketManager.hpp"

SocketManager::SocketManager()
{
	_PollListSize = 0;
}

SocketManager::SocketManager(std::vector<t_socket_info>	socketInitInfo)
{
	try
	{
		for(std::vector<t_socket_info>::size_type i = 0; i != socketInitInfo.size(); i++)
		{
			_SocketList.push_back( new Socket(socketInitInfo[i].host, socketInitInfo[i].port));		//create the socket and store it's pointer in a vector
			_SocketList.back()->bind_socket();													//bind the socket to the port
			_SocketList.back()->start_listening(MAXQUEUESIZE);									//start the socket in listen (receive) mode with a queue size of 
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		for (std::vector<Socket*>::size_type i = 0; i < _SocketList.size(); i++)					//delete all the sockets if there is an error somewhere
		{
			delete _SocketList[i];
		}
	}
	_PollListSize = 0;
}

SocketManager::SocketManager(const SocketManager& srcSocketManager)
{
	_SocketList = srcSocketManager._SocketList;
	_ActiveConnectionList = srcSocketManager._ActiveConnectionList;
	_PollListSize = 0;
}

void	SocketManager::fillPollList( void )
{
	if (_PollListSize > 0)
		delete[] _PollList;
	_PollListSize = _SocketList.size() + _ActiveConnectionList.size();
	_PollList = new pollfd[_PollListSize];
	for (int i = 0; i < _SocketList.size(); i++)
	{
		_PollList[i].fd = _SocketList.at(i)->getFD();
		_PollList[i].events = POLLIN;
		_PollList[i].revents = 0;
	}
	for (int i = 0; i < _ActiveConnectionList.size(); i++)
	{
		_PollList[i + _SocketList.size()].fd = _ActiveConnectionList.at(i)->GetConnectionFD();
		_PollList[i + _SocketList.size()].events = POLLIN;
		_PollList[i + _SocketList.size()].revents = 0;
	}
}

int		SocketManager::cycle(int timeout)
{
	//main function of the manager
	//	-add all sockets and connections to the poll list
	this->fillPollList();
	//	-use epoll to monitor all sockets until one has a connection
	poll(_PollList, _PollListSize, timeout);
	//	-create new connections for sockets that have them
	//	-handle connections that can be read from (ignoring the ones created previously to give clients time to send requests)
	//	-close connections older than their timeout and cleanup
}

SocketManager::~SocketManager()
{
	for (std::vector<Socket*>::size_type i = 0; i < _SocketList.size(); i++)					//delete all the sockets if there is an error somewhere
	{
		delete _SocketList[i];
	}
}