# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 11:39:56 by dimitriscr        #+#    #+#              #
#    Updated: 2022/05/31 11:45:18 by dimitriscr       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98
RM = rm -rf

SRCS = srcs/main.cpp

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
