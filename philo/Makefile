# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamarinc <mamarinc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 15:34:03 by mamarinc          #+#    #+#              #
#    Updated: 2024/05/03 15:24:50 by mamarinc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -g
SRCS = philo.c \
	   utils.c \
	   init_structs.c \
	   check_args.c \
	   philo_life.c \
	   main.c

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "\033[38;5;48mphilo ready\033[0m"

%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
