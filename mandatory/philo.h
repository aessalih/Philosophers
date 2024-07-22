/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:29:37 by aessalih          #+#    #+#             */
/*   Updated: 2024/07/21 11:52:03 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int				philoIndex;
	int				philoFork;
	struct s_philo	*next;
} t_philo;

typedef struct s_info
{
	long	numOfphilo;
	long	timeToDie;
	long	timeToEat;
	long	timeToSleep;
	long	numOfMeals;
} t_info;


void	check_args(int ac, char **av);
t_philo	*create_philos(char **av);
void	parse_args(int ac, char **av, t_info *info);

#endif