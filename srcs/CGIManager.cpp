/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIManager.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:11:06 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/10/06 22:26:48 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

CGIManager::CGIManager()
{
}

CGIManager::CGIManager(Request &request, conf config, location location)
{
	_request = request;
	_config = config;
	_location = location;
	this->initEnv();
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
	char	buffer[256];

	_env["REDIRECT_STATUS"] = "200";
	_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	_env["CONTENT_TYPE"] = "text/plain";
	_env["HTTP_ACCEPT-ENCODING"] = "gzip";
	_env["HTTP_HOST"] = "localhost";
	_env["HTTP_USER-AGENT"] = "Go-http-client/1.1";
	_env["REMOTE_ADDR"] = "127.0.0.1";
	_env["CONTENT_LENGTH"] = _request._Body.size();
	_env["SERVER_NAME"] = _config.get_ServerName().at(0);
	_env["SERVER_SOFTWARE"] = SERVER_VERS;
	_env["SERVER_PROTOCOL"] = HTTP_VERS;
	_env["SERVER_PORT"] = SSTR(_config.get_Port());
	_env["REQUEST_METHOD"] = _request._Method;
	_env["REQUEST_URI"] = _request._Path;
	_env["SCRIPT_FILENAME"] = get_ressource_location(_location, _request._Path);
	_env["SCRIPT_NAME"] = _location._cgi.second;
	_env["PATH_INFO"] = _request._Path;
	_env["PATH_TRANSLATED"] = _location._root + _request._Path.substr(_location._path.size());
	_env["DOCUMENT_ROOT"] = _location._root;
	_env["QUERY_STRING"] = _request._Query; //see here
	if (_env["SCRIPT_NAME"].substr(0, 2) == "./")
		_env["SCRIPT_NAME"].replace(0, 1, getcwd(&buffer[0], 256));
	// if (_request.key_exists("X-Secret-Header-For-Test:"))
	// 	_env["X-Secret-Header-For-Test"] = _request.get_keyval("X-Secret-Header-For-Test:").value;
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
    char            **env;
	std::string		retstr;

    env = this->charArray();

	char *args[] = {
		(char*)_location._cgi.second.c_str(),
		(char*)_env["SCRIPT_NAME"].c_str(),
		NULL
	};

	std::ofstream tempfile(".tempcgi");
	tempfile << _request._Body.c_str();
	tempfile.close();
	std::ofstream tempfile2(".tempcgiout");
	tempfile.close();

    pid = fork();

    if (pid == -1)
	{
		remove(".tempcgiout");
		remove(".tempcgi");
        return ("Error Status 500"); //fork failed return error
    }
    else if (!pid)
    {
		int	fd;
		int fdout;

		fd = open(".tempcgi", O_RDONLY);
		fdout = open(".tempcgiout", O_WRONLY | O_CREAT);
		if (fd != -1 && fdout != -1)
		{
			dup2(fdout, STDOUT_FILENO);
			dup2(fd, STDIN_FILENO);
			close(fd);
			execve((_location._cgi.second).c_str(), args, env);
		}
		write(STDOUT_FILENO, "Error Status 500", 16); // if program gets this far execve has failed
    }
    else
    {
		waitpid(pid, NULL, 0);

		std::string outtext;
		std::ifstream readfile (".tempcgiout");
		while (getline(readfile, outtext))
		{
			retstr += outtext;
		}
		readfile.close();
		remove(".tempcgiout");
		remove(".tempcgi");
	}

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
