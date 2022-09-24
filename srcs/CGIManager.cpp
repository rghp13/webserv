/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIManager.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:11:06 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/24 17:10:19 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/CGIManager.hpp"

CGIManager::CGIManager()
{
}

CGIManager::CGIManager(Request request, conf config, location location)
{
	_request = request;
	_config = config;
	_location = location;
}

CGIManager::CGIManager(const CGIManager &src)
{
	_location = src._location;
	_request = src._request;
	_config = src._config;
	_env = src._env;
}

void    CGIManager::initEnv()
{
	_env["REDIRECT_STATUS"] = "200";
	_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	_env["SERVER_NAME"] = _config.get_ServerName().at(0);
	_env["SERVER_SOFTWARE"] = SERVER_VERS;
	_env["SERVER_PROTOCOL"] = HTTP_VERS;
	_env["SERVER_PORT"] = SSTR(_config.get_Port());
	_env["REQUEST_METHOD"] = _request._Method;
	_env["SCRIPT_NAME"] = _request._Path.replace(0, _location._path.size(), _location._root); //see here
	_env["DOCUMENT_ROOT"] = _location._root;
	_env["QUERY_STRING"] = "Doesntworkyet"; //see here
	//probably needs authentification headers
}

char    **CGIManager::charArray( void ) const
{
	char	**env = new char*[_env.size() + 1];
	int		j = 0;
	for (std::map<std::string, std::string>::const_iterator i = _env.begin(); i != _env.end(); i++)
	{
		std::string		element = i->first + "=" + i->second;
		env[j] = new char[element.size() + 1];
		env[j] = strcpy(env[j], (const char*)element.c_str());
		j++;
	}
	env[j] = NULL;
	return (env);
	
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
	write(sendpipe[1], _request._Body.c_str(), _request._Body.size());

    pid = fork();

    if (pid == -1)
    {
        return ("Error"); //fork failed return error
    }
    else if (!pid)
    {
        //created process
		dup2(sendpipe[0], STDIN_FILENO);
		dup2(recvpipe[1], STDOUT_FILENO);
		execve((_location._cgi.second + _env["SCRIPT_NAME"]).c_str(), NULL, env);
		write(STDOUT_FILENO, "Error Status 500", 16); // if program gets this far execve has failed
    }
    else
    {
        //stil this process
		waitpid(-1, NULL, 0);

		char	buffer[1025] = {0};
		int		ret			 = 1024;

		while (ret == 1024)
		{
			read(recvpipe[0], buffer, 1024);
			buffer[ret] = '\0';
			retstr += buffer;
		}
    }

	close(sendpipe[0]);
	close(sendpipe[1]);
	close(recvpipe[0]);
	close(recvpipe[1]);
	//if child process gets this far, close it

	for (size_t i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;

	if (!pid)
		exit(0);

	return (retstr);
}

CGIManager::~CGIManager()
{
}
