/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:12:52 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/06 13:00:17 by dimitriscr       ###   ########.fr       */
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

void	SocketManager::createNewConnections( void )
{
	for (int i = 0; i < _SocketList.size(); i++)
	{
		if (_PollList[i].revents != 0)
		{
			for (int j = 0; j < _SocketList.size(); j++)
			{
				if (_SocketList[j]->getFD() == _PollList[i].fd)
				{
					_ActiveConnectionList.push_back(new Connection(_PollList[i].fd, _SocketList[j]->getPortHost()));
				}
			}
		}
	}

}

void	SocketManager::handleRequests( void )
{
	//for each socket that has data, read, pass to rponson's code and send answer
}

void	SocketManager::cleanConnections( void )
{
	//run through all connection and close all the ones that havn't been used in a while
	for (int i = 0; i < _ActiveConnectionList.size(); i++)
	{
		if (_ActiveConnectionList[i]->ShouldDestroy())
		{
			delete _ActiveConnectionList[i];
			_ActiveConnectionList.erase(_ActiveConnectionList.begin() + i);
		}
	}
}

int		SocketManager::cycle(int timeout)
{
	//main function of the manager
	//	-add all sockets and connections to the poll list
	this->fillPollList();
	//	-use epoll to monitor all sockets until one has a connection
	if (poll(_PollList, _PollListSize, timeout) > 0)
	{
		//	-create new connections for sockets that have them
		this->createNewConnections();
		//	-handle connections that can be read from (ignoring the ones created previously to give clients time to send requests)
		this->handleRequests();
	}
	//	-close connections older than their timeout and cleanup
	this->cleanConnections();
	return (1);
}

SocketManager::~SocketManager()
{
	for (std::vector<Socket*>::size_type i = 0; i < _SocketList.size(); i++)					//delete all the sockets if there is an error somewhere
	{
		delete _SocketList[i];
	}
}