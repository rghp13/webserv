/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:43:03 by rponsonn          #+#    #+#             */
/*   Updated: 2022/09/08 16:33:38 by rponsonn         ###   ########.fr       */
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