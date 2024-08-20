/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:29:37 by aessalih          #+#    #+#             */
/*   Updated: 2024/08/19 14:39:36 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4

typedef struct s_philo
{
	pthread_t		thread;
	int				philoindex;
	int				philofork;
	int				*dead;
	long			numofphilo;
	long			timetodie;
	long			timetoeat;
	long			timetosleep;
	long			numofmeals;
	double			lastmeal;
	double			time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*lock;
	struct s_philo	*next;
	struct s_philo	*previous;
}	t_philo;

typedef struct s_info
{
	long	numofphilo;
	long	timetodie;
	long	timetoeat;
	long	timetosleep;
	long	numofmeals;
	int		dead;
}	t_info;

int		check_args(int ac, char **av);
t_philo	*create_philos(t_info *info);
t_info	*parse_args(int ac, char **av);
void	ft_free(t_philo *philo);
void	ft_start(t_philo *philos, long numofphilo);
void	*routine(void *philo);
double	gettime();
int		ft_sleep(long timetosleep);
void	ft_print_sleep(t_philo *t, double time);
void	ft_eat(t_philo *t, double time);
void	ft_think(t_philo *t, double time);
void	custom_print(t_philo *t, double time, int flag);
void	custom_print(t_philo *t, double time, int flag);

#endif