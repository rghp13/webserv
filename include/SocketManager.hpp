/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:59:33 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/09/05 15:29:40 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

class SocketManager
{
private:
    std::vector<Socket>		_SocketList;
	//list of opened connections
public:
    SocketManager();
    SocketManager(std::vector<t_socket_info> socketInitInfo);
    SocketManager(const SocketManager& srcSocketManager);
    ~SocketManager();
};

