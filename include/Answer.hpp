/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Answer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:45:24 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/04 22:18:13 by dimitriscr       ###   ########.fr       */
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
	std::vector<t_header_argument>	_Arguments;
	std::string						_Body;
	Answer();
	Answer	&operator=(Answer const &src);
	bool			AddArgument (t_header_argument newArg);
	std::string		MakeString( void ) const;
	int				SetBodyLen( void );
	~Answer();
};

#endif