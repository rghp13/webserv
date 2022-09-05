/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Answer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:46:27 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/05 18:27:38 by rponsonn         ###   ########.fr       */
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

void	Answer::AddArgument(t_header_argument newArg)
{
	//check if key is already in
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

std::string	Answer::MakeString( void ) const
{
	//function that will create a fully "stringify" version of
	//the answer ready to be sent to the client
	return ("");
}

int		Answer::SetBodyLen( void )
{
	//Adds or replaces the Content-Length argument to match the
	//size of the body (also returns it in case it is needed)
	return (0);
}