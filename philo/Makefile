# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: resilva <resilva@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 19:26:29 by resilva           #+#    #+#              #
#    Updated: 2024/09/14 19:26:29 by resilva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread
INCLUDE = -I include
MAKE = make -C
DN = > /dev/null

SRC =	$(wildcard src/*.c)

# ------------------------------ Colors ------------------------------

BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_GREEN	=	\033[1;32m
BOLD_YELLOW	=	\033[1;33m
NO_COLOR	=	\033[0m

# ------------------------------ Message ------------------------------

COMP_START	=	echo "\n $(BOLD_YELLOW)Make: $(NO_COLOR)Starting the compilation...\n"

READY		=	echo "\n $(BOLD_GREEN)Ready$(NO_COLOR) : The program $(BOLD_CYAN) philo $(NO_COLOR)has been compiled!\n"

CLEANED		=	echo "\n $(BOLD_PURPLE)Clean: $(NO_COLOR)Removed all the \".o\" files \n"

FCLEANED	=	echo "\n $(BOLD_PURPLE)Fclean: $(NO_COLOR)Removed the executables \n"


.c.o:
	@${CC} ${FLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

OBJ = ${SRC:.c=.o}

${NAME}: ${OBJ}
		@$(COMP_START)
		@${CC} ${FLAGS} ${INCLUDE} ${OBJ} -o ${NAME} -pthread
		@$(READY) 

all: ${NAME}

clean:
	@${RM} ${OBJ}
	@$(CLEANED)

fclean: clean
	@${RM} ${NAME}
	@$(FCLEANED)

re: fclean all

.PHONY: all clean fclean re