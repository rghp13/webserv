/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:43:03 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/01 19:54:37 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

bool	isdir(std::string input)
{
	struct stat s;
	
	if (stat(input.c_str(), &s) == 0)
	{
		if (s.st_mode & S_IFDIR || s.st_mode & S_IFREG)
			return (true);
	}
	return (false);
}

std::string	generateDirectoryPage(std::string dirPath, std::string docroot)
{
	DIR	*dir;
	struct dirent	*file;
	std::string		retstr;
	
	dir = opendir((docroot + dirPath).c_str());
	if (dir == NULL)
		return ("");
	retstr = "<html><head>\n<title>Index of /";
	retstr += dirPath;
	retstr += "</title>\n</head>\n<body>\n\n<title>Index of ";
	retstr += dirPath;
	retstr += "</title>\n<h1>Index of ";
	retstr += dirPath;
	retstr += "</h1>\n<table>\n<tbody><tr><th>Content</th><th></tr>\n<tr><th colspan=\"4\"><hr></th></tr>\n";
	while ((file = readdir(dir)) != NULL) 
	{
		if (file->d_type == DT_DIR)
		{
			retstr += "<tr><td valign=\"top\"><img src=\"https://cdn4.iconfinder.com/data/icons/ionicons/512/icon-folder-20.png\" alt=\"[DIR]\"></td><td><a href=\"";
			retstr += file->d_name;
			retstr += "/\">";
			retstr += file->d_name;
			retstr += "/</a></td></tr>\n";
		}
		else
		{
			retstr += "<tr><td valign=\"top\"><img src=\"https://cdn1.iconfinder.com/data/icons/andriod-app/32/drive-file-20.png\" alt=\"[TXT]\"></td><td><a href=\"";
			retstr += file->d_name;
			retstr += "\">";
			retstr += file->d_name;
			retstr += "</a></td></tr>\n";
		}
	}
	retstr += "<tr><th colspan=\"4\"><hr></th></tr>\n</tbody></table>\n</li></div></body></html>\n";
	closedir(dir);
	return (retstr);
}

void	ascii_codes(std::string &string)
{
	std::size_t found = string.find('%');
	char		codeval;
	while (found != string.npos)
	{
		codeval = std::strtol(string.substr(found + 1, 2).c_str(), NULL, 16);
		string.replace(found, 3, 1, codeval);
		found = string.find('%');
	}
	return ;
}
void	location_clear(location &loc)
{
	loc._path.clear();
	loc._methods = 0;
	loc._redirection.first = 0;
	loc._redirection.second.clear();
	loc._root.clear();
	loc._index.clear();
	loc._autoindex = false;
	loc._cgi.first.clear();
	loc._cgi.second.clear();
	loc._uploaddir.clear();
}
int	check_locroot(conf &temp)
{
	std::vector<location> loc = temp.get_location();
	std::vector<location>::iterator iter = loc.begin();
	while(iter != loc.end())
	{
		if (iter->_path == "/")
			return (0);
		iter++;
	}
	return (1);
}

void	print_answer_debug(Answer answer)
{
	if (answer._StatusCode <= 299)
		std::cout << "\033[42mSent answer with code " << answer._StatusCode << "\033[0m" << std::endl;
	else if (answer._StatusCode <= 399)
		std::cout << "\033[43mSent answer with code " << answer._StatusCode << "\033[0m" << std::endl;
	else
		std::cout << "\033[41mSent answer with code " << answer._StatusCode << "\033[0m" << std::endl;
	return;
}