# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 11:39:56 by dimitriscr        #+#    #+#              #
#    Updated: 2022/06/11 02:36:19 by dimitriscr       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define HEADER
██╗    ██╗███████╗██████╗ ███████╗███████╗██████╗ ██╗   ██╗
██║    ██║██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██║   ██║
██║ █╗ ██║█████╗  ██████╔╝███████╗█████╗  ██████╔╝██║   ██║
██║███╗██║██╔══╝  ██╔══██╗╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝
╚███╔███╔╝███████╗██████╔╝███████║███████╗██║  ██║ ╚████╔╝ 
 ╚══╝╚══╝ ╚══════╝╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  
                                                           
endef
export HEADER

NC = \033[0m
RED = \033[0;91m
ORANGE = \033[93m
GREEN = \033[32m
PURPLE = \033[0;95m
BLUE = \033[0;34m
BOLD = \033[1m
CYAN = \033[36m

PATH_SRC				=		./srcs
PATH_HEAD				=		./includes
SRC_NAME				=		Socket.cpp \
								Request.cpp \
								Answer.cpp \
								init_sockets.cpp \
								socket_poll.cpp \
								create_connection.cpp \
								main.cpp

NAME					=		webserv
OBJ_NAME				=		$(SRC_NAME:.cpp=.o)
CC						=		c++
RM						=		rm -f
CFLAGS					=		-Wall -Werror -Wextra -std=c++98
SRC						=		$(addprefix $(PATH_SRC)/,$(SRC_NAME))
OBJ						=		$(addprefix $(PATH_SRC)/,$(OBJ_NAME))
.cpp.o:
								@${CC} ${CFLAG} -I${PATH_HEAD} -c $< -o ${<:.cpp=.o}
								@printf "${GREEN}[ OK ] ${<:.s=.o}${NC}                \r"
${NAME}:						${OBJ}
								@printf "${GREEN}[DONE]${NC}\n"
								@${CC} $^ -o $@ ${CFLAG}
								@printf "${CYAN}[COMPILATION COMPLETE]${NC}\n"
								@printf "${PURPLE}$$HEADER${NC}\n"
all:							${NAME}

clean:
								@${RM} ${OBJ}
								@printf "\n${GREEN}[ OK ]${NC}${RED} *.o files DELETED${NC}\n"
fclean:							clean
								@${RM} ${NAME}
								@printf "${GREEN}[ OK ]${NC}${RED} ${NAME} DELETED${NC}\n"
re:								fclean ${NAME}
.PHONY:							all clean fclean re
