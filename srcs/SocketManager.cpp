/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:12:52 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/10/06 04:40:10 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

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
	for (unsigned long i = 0; i < _SocketList.size(); i++)
	{
		_PollList[i].fd = _SocketList.at(i)->getFD();
		_PollList[i].events = POLLIN | POLLOUT | POLLHUP;
		_PollList[i].revents = 0;
	}
	for (unsigned long i = 0; i < _ActiveConnectionList.size(); i++)
	{
		_PollList[i + _SocketList.size()].fd = _ActiveConnectionList.at(i)->GetConnectionFD();
		_PollList[i + _SocketList.size()].events = POLLIN | POLLOUT | POLLHUP;
		_PollList[i + _SocketList.size()].revents = 0;
	}
}

void	SocketManager::createNewConnections( void )
{
	for (unsigned long i = 0; i < _SocketList.size(); i++)
	{
		if (_PollList[i].revents == POLLIN)
		{
			for (unsigned long j = 0; j < _SocketList.size(); j++)
			{
				if (_SocketList[j]->getFD() == _PollList[i].fd)
				{
					_ActiveConnectionList.push_back(new Connection(_SocketList[j]->accept_connection(), _SocketList[j]->getPortHost()));
					break;
				}
			}
		}
	}
}

void	SocketManager::handleRequests(std::vector<conf> Vconf)
{
	Answer		tempanswer;
	std::string	request;
	//for each socket that has data, read, pass to rponson's code and send answers
	for (int i = _SocketList.size(); i < _PollListSize; i++)
	{
		if (_PollList[i].revents == POLLIN)
		{
			for (unsigned long j = 0; j < _ActiveConnectionList.size(); j++)
			{
				if (_ActiveConnectionList[j]->GetConnectionFD() == _PollList[i].fd)
				{
					request = _ActiveConnectionList[j]->GetNewestClientRequest();
					if (request.size() != 0)
					{
						if (DEBUG_LVL > 2)
							std::cout << request << std::endl;
						Request	temprequest(_ActiveConnectionList[j]->GetPort(), _ActiveConnectionList[j]->GetHost(), request);
						tempanswer = fork_request(temprequest, Vconf);
						if (DEBUG_LVL > 1)
							print_answer_debug(tempanswer);
						_ActiveConnectionList[j]->setAnswer(tempanswer.MakeString());
					}
					break;
				}
			}
		}
	}
	
}

void	SocketManager::cleanConnections( void )
{
	//run through all connection and close all the ones that havn't been used in a while or that have had their client disconnect
	for (int i = _SocketList.size(); i < _PollListSize; i++)
	{
		for (unsigned long j = 0; j < _ActiveConnectionList.size(); j++)
		{
			if (_ActiveConnectionList[j]->GetConnectionFD() == _PollList[i].fd)
			{
				if (_ActiveConnectionList[j]->ShouldDestroy() || (_PollList[i].revents&POLLERR) == POLLERR || (_PollList[i].revents&POLLHUP) == POLLHUP || _ActiveConnectionList.size() > 5)
				{
					Answer	temp;
					temp.SetStatus(HTTP_ERR_408);
					_ActiveConnectionList[j]->setAnswer(temp.MakeString());
					_ActiveConnectionList[j]->SendAnswer();
					delete _ActiveConnectionList[j];
					_ActiveConnectionList.erase(_ActiveConnectionList.begin() + j);
				}
			}
		}
	}
}

int		SocketManager::cycle(int timeout, std::vector<conf> Vconf)
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
		this->handleRequests(Vconf);
		// -handle sending to connections that can send and have an available answer
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