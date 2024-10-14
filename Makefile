# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 10:34:17 by aessalih          #+#    #+#              #
#    Updated: 2024/10/14 13:47:37 by aessalih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

M_SRC = mandatory/philo.c mandatory/check_arguments.c mandatory/parse_args.c mandatory/create_philos.c \
	mandatory/ft_start.c mandatory/ft_free.c mandatory/ft_actions.c mandatory/ft_sleep.c mandatory/ft_mutex.c \
	mandatory/ft_start_numofmeals.c

O_M_SRC = $(M_SRC:.c=.o)

CC= cc
CFLAGS= -Werror -Wextra -Wall

NAME=philo

mandatory/%.o: mandatory/%.c mandatory/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(O_M_SRC)
	$(CC) $(CFLAGS) $(O_M_SRC) -o $(NAME)

clean:
	rm -f $(O_B_SRC) $(O_M_SRC)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all