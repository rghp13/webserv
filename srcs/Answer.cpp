/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Answer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:46:27 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/09 14:35:41 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Answer.hpp"

Answer::Answer()
{
	_HTTPVersion = HTTP_VERS;
	_StatusCode = 200;
	_StatusMessage = "OK";
	//place any arguments that are always the same here
	//Server
	_Body = "";
}
Answer::Answer(int erno)
{
	_HTTPVersion = HTTP_VERS;
	_StatusCode = erno;
	_Body = "";
	if (erno == 404)
		SetStatus(HTTP_ERR_404);
	else if (erno == 403)
		SetStatus(HTTP_ERR_403);

}
Answer::~Answer()
{
}

Answer	&Answer::operator=(Answer const &src)
{
	_HTTPVersion = src._HTTPVersion;
	_StatusCode = src._StatusCode;
	_StatusMessage = src._StatusMessage;
	_Arguments = src._Arguments;
	_Body = src._Body;
	return (*this);
}

void	Answer::SetStatus(int code, std::string message)
{
	_StatusCode = code;
	_StatusMessage = message;
	if (code != 200)
		this->GenerateErrorBody();
}

void	Answer::GenerateErrorBody( void )
{
	_Body = "<!DOCTYPE html>\n<html lang=”en”>\n<head>\n<title></title>\n</head>\n<body>\n<div style=\"text-align: center;\">\n<h1>Oh No!</h1>\n<p>We have encountered an issue!</p>\n<img src=\"https://http.cat/";
	_Body += SSTR(_StatusCode);
	_Body += ".jpg\">\n</div>\n</body>\n</html>";
	this->SetBodyLen();
}

void	Answer::AddArgument(t_header_argument newArg)
{
	//if key already exists will overwrite value
	std::vector<t_header_argument>::iterator it = _Arguments.begin();
	while (it != _Arguments.end())
	{
		if (newArg.key == it->key)
		{
			it->value = newArg.value;
			return;
		}
		it++;
	}
	_Arguments.push_back(newArg);
}

std::string	Answer::MakeString( void )
{
	//function that will create a fully "stringify" version of
	//the answer ready to be sent to the client
	std::string ret;
	SetBodyLen();
	ret += _HTTPVersion + " ";
	ret += SSTR(_StatusCode);
	ret += " " + _StatusMessage + HTTPNL;
	
	for(std::vector<t_header_argument>::iterator i = _Arguments.begin(); i != _Arguments.end(); i++)
	{
		ret += i->key + " ";
		ret += i->value + HTTPNL;
	}
	ret += HTTPNL + _Body;
	return (ret);
}

int		Answer::SetBodyLen( void )
{
	//Adds or replaces the Content-Length argument to match the
	//size of the body (also returns it in case it is needed)
	t_header_argument ret;
	ret.value = SSTR(_Body.length());
	ret.key = "Content-Length:";
	AddArgument(ret);
	return (_Body.length());
}