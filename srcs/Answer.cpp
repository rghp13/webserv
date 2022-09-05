/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Answer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:46:27 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/04 22:15:03 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Answer.hpp"

Answer::Answer()
{
	_HTTPVersion = HTTP_VERS;
	_StatusCode = 200;
	_StatusMessage = "OK";
	//place any arguments that are always the same here
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

bool	Answer::AddArgument(t_header_argument newArg)
{
	//Function that will add an argument to the vector if it doesn't
	//exist and replace it if it does
	return (true);
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