/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Answer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:46:27 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/11 02:45:57 by dimitriscr       ###   ########.fr       */
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
