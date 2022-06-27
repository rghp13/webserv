/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:40:51 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/26 17:35:11 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

int main(int argc, char **argv)
{
	std::ifstream argfile;
	if (boot_check(argc, argv, argfile))
		return (1);
	//initialization:
	std::vector<conf> Vconf;
	init(Vconf, argfile);
	for (std::vector<conf>::iterator i = Vconf.begin(); i != Vconf.end(); i++)
		i->print();
	// -check config file
	// -load config file
	// -get a list of all prots that nned websockets

	//loop
	// -start websockets on each of the ports

	//cleanup
	return (0);
}