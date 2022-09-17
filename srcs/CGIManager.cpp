/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIManager.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:11:06 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/16 21:10:29 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/CGIManager.hpp"

CGIManager::CGIManager()
{
}

CGIManager::CGIManager(Request request, conf config)
{
}

CGIManager::CGIManager(const CGIManager &src)
{
}

void    CGIManager::initEnv(Request request, conf config)
{
}

char    **CGIManager::charArray( void ) const
{
}

std::string CGIManager::runCGI( void )
{
    pid_t           pid;
    int             sendpipe[2];
    int             recvpipe[2];
    char            **env;
    std::string     retstr;

    env = this->charArray();
    //if this alloc fails return 500

    pipe(sendpipe);
    pipe(recvpipe);
    //this needs error checking

    //write what needs to be written to sendpipe[1]

    pid = fork();

    if (pid == -1)
    {
        return ("Error"); //fork failed return error
    }
    else if (!pid)
    {
        //created process
    }
    else
    {
        //stil this process
    }
}

CGIManager::~CGIManager()
{
}
