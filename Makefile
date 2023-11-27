# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlevilla <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 13:41:06 by rlevilla          #+#    #+#              #
#    Updated: 2023/11/27 21:08:39 by rlevilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	main.c \
		utils.c \
		init.c \
		check_death.c \
		routine.c \

CC = gcc

LEAKS = leaks -atExit --

CFLAGS = -Wall -Wextra -Werror

NAME = philo

OBJ = $(SRC:.c=.o)

all: $(NAME)

.c .o:
		$(CC) -c $< -o $(<:.c=.o)

RM = rm -f

# Compile tout, sous le nom philo
${NAME}:	${OBJ}
			${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean:	
		$(RM) $(OBJ) $(NAME)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all
