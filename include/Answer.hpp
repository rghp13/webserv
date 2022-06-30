/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Answer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:45:24 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/29 15:20:09 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANSWER_HPP
 #define ANSWER_HPP
#include <string>

class Answer
{
private:

public:
	bool		RequestErrored;
	int			ErrorCode;
	std::string	ReturnedContent;
	Answer();
	Answer(int newErrorCode);
	Answer(std::string newContent);
	~Answer();
	Answer	&operator=(Answer const &src);
};

#endif