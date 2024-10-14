/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:22:57 by aessalih          #+#    #+#             */
/*   Updated: 2024/10/14 13:38:41 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_isdied(t_philo *t, long *checktime)
{
	pthread_mutex_lock(t->dead_flag);
	if ((gettime() - *checktime) > t->timetodie)
	{
		pthread_mutex_lock(t->dead_lock);
		*t->dead = t->philoindex;
		pthread_mutex_unlock(t->dead_lock);
		custom_print(t, *checktime, DEATH);
	}
	pthread_mutex_unlock(t->dead_flag);
}

void	custom_print(t_philo *t, long time, int flag)
{
	pthread_mutex_lock(t->print_lock);
	if (flag == DEATH)
		printf("%ld %d is died\n", (gettime() - time), t->philoindex);
	pthread_mutex_lock(t->dead_lock);
	if (flag == FORK && *t->dead == 0)
		printf("%ld %d has taken a fork\n", (gettime() - time), t->philoindex);
	else if (flag == EAT && *t->dead == 0)
		printf("%ld %d is eating\n", (gettime() - time), t->philoindex);
	else if (flag == SLEEP && *t->dead == 0)
		printf("%ld %d is sleeping\n", (gettime() - time), t->philoindex);
	else if (flag == THINK && *t->dead == 0)
		printf("%ld %d is thinking\n", (gettime() - time), t->philoindex);
	pthread_mutex_unlock(t->dead_lock);
	pthread_mutex_unlock(t->print_lock);
}

void	*routine(void *philo)
{
	t_philo	*t;

	t = (t_philo *)philo;
	pthread_mutex_lock(t->dead_flag);
	t->lastmeal = gettime();
	pthread_mutex_unlock(t->dead_flag);
	while (1)
	{
		pthread_mutex_lock(t->dead_lock);
		if (*t->wait != 0)
		{
			pthread_mutex_unlock(t->dead_lock);
			break ;
		}
		pthread_mutex_unlock(t->dead_lock);
	}
	if (t->philoindex % 2) {
		usleep(t->timetoeat / 2);
	}
	// if (t->philoindex % 2 == 1)
	// 	usleep(1000);
	while (1)
	{
		if (ft_simulation(t))
			break ;
	}
	return (NULL);
}

void	monitor(t_philo *philos, long numofphilo)
{
	int	i;

	i = 0;
	while (1)
	{
		ft_isdied(philos, &philos->lastmeal);
		pthread_mutex_lock(philos->dead_lock);
		if (*philos->dead != 0)
		{
			pthread_mutex_unlock(philos->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philos->dead_lock);
		philos = philos->next;
	}
	i = 0;
	while (i < numofphilo)
	{
		if (pthread_join(philos->thread, NULL))
			write(2, "pthread_detach failed\n", 28);
		philos = philos->next;
		i++;
	}
}

void	ft_start(t_philo *philos, long numofphilo)
{
	int		i;

	initialize_mutex(philos);
	i = 0;
	while (i < numofphilo)
	{
		if (pthread_create(&philos->thread, NULL, &routine, philos))
			perror("pthread_create function failed\n");
		(1) && (philos = philos->next, i++);
	}
	*philos->time = gettime();
	pthread_mutex_lock(philos->dead_lock);
	*philos->wait = 1;
	pthread_mutex_unlock(philos->dead_lock);
	usleep(5);
	(monitor(philos, numofphilo), destroy_mutex(philos));
}
