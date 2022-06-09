/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:40:51 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/10 00:15:25 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

int main(int argc, char **argv)
{
	//initialization:
	// -check config file
	// -load config file
	// -get a list of all prots that nned websockets

	//start websockets on each of the ports

	//loop
	//	-use epoll to monitor all sockets until one has a connection
	//	-parse request from socket
	//	-use config file to find which page corresponds to the request
	//	-append header to content and send to client
	//	-close connection and cleanup

	//cleanup
	(void)argc;
	(void)argv;
	return (0);
}