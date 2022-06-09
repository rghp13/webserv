/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:40:51 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/06/09 15:22:25 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: Too many ARGS\n";
		return (0);
	}
	else if (argc == 2)
	{
		//open file
	}
	//initialization:
	std::vector<conf> Vconf;
	init(Vconf);
	// -check config file
	// -load config file
	// -get a list of all prots that nned websockets

	//loop
	// -start websockets on each of the ports

	//cleanup
	return (0);
}