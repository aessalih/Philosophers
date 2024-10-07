# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 10:34:17 by aessalih          #+#    #+#              #
#    Updated: 2024/10/07 15:42:54 by aessalih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

M_SRC = mandatory/philo.c mandatory/check_arguments.c mandatory/parse_args.c mandatory/create_philos.c \
	mandatory/ft_start.c mandatory/ft_free.c mandatory/ft_actions.c mandatory/ft_sleep.c mandatory/ft_mutex.c \
	mandatory/ft_start_numofmeals.c

O_M_SRC = $(M_SRC:.c=.o)

CC= cc
CFLAGS= -fsanitize=thread -g -Werror -Wextra -Wall #-fsanitize=thread -g

NAME=philo

# NAME_BONUS=philo_bonus

# bonus/%.o: bonus/%.c bonus/philo_bonus.h
# 	$(CC) $(CFLAGS) -c $^ -o $@

azz: all clean
	clear

mandatory/%.o: mandatory/%.c mandatory/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

# bonus: $(NAME_BONUS)

$(NAME): $(O_M_SRC)
	$(CC) $(CFLAGS) -fsanitize=thread -g -pthread $(O_M_SRC) -o $(NAME)

# $(NAME_BONUS): $(O_B_SRC)
# 	$(CC) $(CFLAGS) $(O_B_SRC) -o $(NAME_BONUS)

clean:
	rm -f $(O_B_SRC) $(O_M_SRC)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all