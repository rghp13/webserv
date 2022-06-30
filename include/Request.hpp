/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:10:15 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/30 19:53:46 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
 #define REQUEST_HPP
#include <string>
#include <algorithm>

class Request
{
private:

public:
	unsigned int	port;
	std::string		host;
	std::string		domain;
	std::string		pageRequested;
	Request();
	Request(unsigned int newport, std::string newhost, std::string newdomain, std::string newpage);
	Request(unsigned int newport, std::string newhost, std::string newdomain);
	bool	isPageADirectory( void ) const;
	void	htmlize(void);
	~Request();
};

#endif