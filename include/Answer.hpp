/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Answer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:45:24 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/06 17:52:23 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANSWER_HPP
 #define ANSWER_HPP
#include <string>
#include "webserv.hpp"

class Answer
{
private:
public:
	std::string						_HTTPVersion;
	int								_StatusCode;
	std::string						_StatusMessage;
	std::vector<t_header_argument>	_Arguments;//in the future we will have to add some
	std::string						_Body;
	Answer();
	Answer(int erno);
	Answer	&operator=(Answer const &src);
	void			AddArgument (t_header_argument newArg);//adds variables in a key/pair way
	std::string		MakeString( void );//stringify everything in this object
	int				SetBodyLen( void );//runs strlen within _body and stores data in arguments
	~Answer();
};

#endif