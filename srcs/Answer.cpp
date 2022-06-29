/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Answer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:46:27 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/29 15:24:49 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Answer.hpp"

Answer::Answer()
{
	RequestErrored = false;
	ErrorCode = 0;
	ReturnedContent = "";
}

Answer::Answer(int newErrorCode)
{
	RequestErrored = true;
	ErrorCode = newErrorCode;
	ReturnedContent = "";
}

Answer::Answer(std::string newContent)
{
	RequestErrored = false;
	ErrorCode = 0;
	ReturnedContent = newContent;
}

Answer::~Answer()
{
}
Answer	&Answer::operator=(Answer const &src)
{
	RequestErrored = src.RequestErrored;
	ErrorCode = src.ErrorCode;
	ReturnedContent = src.ReturnedContent;
}