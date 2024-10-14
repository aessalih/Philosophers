/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:29:37 by aessalih          #+#    #+#             */
/*   Updated: 2024/10/14 11:05:06 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/_pthread/_pthread_mutex_t.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DEATH 0

typedef struct s_philo
{
	pthread_t		thread;
	int				k;
	int				philoindex;
	int				philofork;
	int				*dead;
	long			numofphilo;
	long			timetodie;
	long			timetoeat;
	long			timetosleep;
	long			numofmeals;
	long			lastmeal;
	long			*time;
	int				*wait;
	int				*flag;
	long			*x;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*dead_flag;
	pthread_mutex_t	*meals;
	struct s_philo	*next;
	struct s_philo	*previous;
}	t_philo;

typedef struct s_info
{
	long			numofphilo;
	long			timetodie;
	long			timetoeat;
	long			timetosleep;
	long			numofmeals;
	long			time;
	int				flag;
	long			x;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*dead_flag;
	pthread_mutex_t	*meals;
	int				dead;
	int				waitphilo;
}	t_info;

int		check_args(int ac, char **av);
t_philo	*create_philos(t_info *info);
t_info	*parse_args(int ac, char **av);
void	ft_free(t_philo *philo);
void	ft_start(t_philo *philos, long numofphilo);
void	ft_start_numofmeals(t_philo *philos, long numofphilo);
void	*routine(void *philo);
long	gettime(void);
int		ft_sleep(long timetosleep);
int		ft_print_sleep(t_philo *t, long time);
int		ft_eat(t_philo *t, long time);
int		ft_think(t_philo *t, long time);
void	custom_print(t_philo *t, long time, int flag);
int		ft_simulation(t_philo *t);
void	initialize_mutex(t_philo *philo);
void	destroy_mutex(t_philo *philo);
void	monitor(t_philo *philos, long numofphilo);
void	ft_isdied(t_philo *t, long *checktime);
int		handle_input(t_info *info);

#endif