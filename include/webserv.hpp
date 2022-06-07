/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:41:19 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/05/31 19:25:28 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
 #define WEBSERV_HPP

#include <string> //string functions
#include <fstream>//unsure, might remove
#include <iostream>

#include <stdlib.h>//apparently exit requires stdlib.h
#include <unistd.h> //read, write, close, etc...
#include <fcntl.h>

#include <netinet/in.h> //variable types that can hold ip addresses
#include <sys/types.h>
#include <sys/socket.h> //socket stuff
#include <sys/select.h>//select
#include <sys/epoll.h>//epoll
#include <arpa/inet.h>//htons htonl ntohs ntohl
#include <poll.h>//poll

#define PORT 80
//research FD_SET, FD_CLR, FD_ISSET, FD_ZERO 
#endif