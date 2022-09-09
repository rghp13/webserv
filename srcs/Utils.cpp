/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:43:03 by rponsonn          #+#    #+#             */
/*   Updated: 2022/09/09 17:03:10 by dscriabi         ###   ########.fr       */
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
	retstr += "</title>\n</head>\n<body>\n\n<title>Index of /";
	retstr += dirPath;
	retstr += "</title>\n<h1>Index of /";
	retstr += dirPath;
	retstr += "</h1>\n<table>\n<tbody><tr><th valign=\"top\"><img src=\"/icons/blank.gif\" alt=\"[ICO]\"></th><th><a href=\"?C=N;O=D\">Name</a></th><th><a href=\"?C=M;O=A\">Last modified</a></th><th><a href=\"?C=S;O=A\">Size</a></th></tr>\n<tr><th colspan=\"4\"><hr></th></tr>\n";
	while ((file = readdir(dir)) != NULL) 
	{
		if (file->d_type == DT_DIR)
		{
			retstr += "<tr><td valign=\"top\"><img src=\"/icons/folder.gif\" alt=\"[DIR]\"></td><td><a href=\"";
			retstr += file->d_name;
			retstr += "/\">";
			retstr += file->d_name;
			retstr += "/</a></td><td align=\"right\">Doesn't Work  </td><td align=\"right\">  - </td></tr>\n";
		}
		else
		{
			retstr += "<tr><td valign=\"top\"><img src=\"/icons/text.gif\" alt=\"[TXT]\"></td><td><a href=\"";
			retstr += file->d_name;
			retstr += "\">";
			retstr += file->d_name;
			retstr += "</a></td><td align=\"right\">Doesn't Work  </td><td align=\"right\"> ";
			retstr += SSTR(file->d_reclen);
			retstr += " </td></tr>\n";
		}
	}
	retstr += "<tr><th colspan=\"4\"><hr></th></tr>\n</tbody></table>\n</li></div></body></html>\n";
	closedir(dir);
	return (retstr);
}