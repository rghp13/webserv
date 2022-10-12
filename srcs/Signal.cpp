/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:45:07 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/10/12 18:52:41 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/webserv.hpp"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		status_changer(1, NULL);
		std::cout << "Shutdown request received, Server is cleaning up before stopping" << std::endl;
	}
}

void	status_changer(int mode, int *status_var)
{
	static int	*status;
	if (mode == 0)
		status = status_var;
	else
		*status = mode;
}