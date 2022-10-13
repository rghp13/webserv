/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:40:51 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/10/13 15:59:03 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

int main(int argc, char **argv)
{
	int							status = 0;		//is 0 while the program should run. Giving it a non-zero value will stop the loop
	std::vector<t_socket_info>	socketInitInfo; //array used to create the sockets on the correct port and host
	std::vector<Socket*>		socketList; 	//array storing pointers to memory allocated socket classes
	std::ifstream				argfile;		//conf file i'll be parsing from
	std::vector<conf> 			Vconf;

	//initialization:
	//signal setup
	status_changer(0, &status);
	std::signal(SIGINT, signal_handler);
	//std::signal(SIGPIPE, signal_handler);
	// -check config file
	if (boot_check(argc, argv, argfile))
		return (1);
	// -load config file
	if (init(Vconf, argfile))
		return (1);
	if (DEBUG_LVL > 0)
	{
		for (std::vector<conf>::iterator i = Vconf.begin(); i != Vconf.end(); i++)
			i->print();
	}
	// -get a list of all prots that need websockets
	fill_socket_vector(socketInitInfo, Vconf);
	if (check_duplicate_socket(socketInitInfo))
		return (1);

	SocketManager	Manager(socketInitInfo);

	while (!status)
	{
		Manager.cycle(10000, Vconf);
	}
	return (0);
}