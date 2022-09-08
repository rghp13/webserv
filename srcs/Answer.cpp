/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Answer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:46:27 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/08 14:48:39 by dscriabi         ###   ########.fr       */
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
	{
		_StatusMessage = "Not Found";
		_Body = "<div id=\"main\"><div class=\"fof\"><h1>Error 404</h1></div></div>";
	}

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
	_Body = "<div id=\"main\"><div class=\"fof\"><h1>Error ";
	_Body += SSTR(_StatusCode);
	_Body += " ";
	_Body += _StatusMessage;
	_Body += "</h1></div></div>";
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