# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 11:39:56 by dimitriscr        #+#    #+#              #
#    Updated: 2022/06/11 16:33:39 by rponsonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CC = c++
CFLAGS = -std=c++98 #-Wall -Werror -Wextra 
RM = rm -rf

SRCS = srcs/main.cpp srcs/init.cpp srcs/conf.cpp

OBJS = $(SRCS:.cpp=.o)

.cpp.o:
			$(CC) $(CFLAGS) -c $< -o ${<:.cpp=.o}

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
