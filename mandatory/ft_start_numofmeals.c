/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_numofmeals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:19:36 by aessalih          #+#    #+#             */
/*   Updated: 2024/10/07 15:49:59 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor2(t_philo *philos, long numofphilo)
{
	int	i;

	i = 0;
	while (1)
	{
		(ft_isdied(philos, &philos->lastmeal), pthread_mutex_lock(philos->dead_lock));
		if (*philos->dead != 0)
		{
			pthread_mutex_unlock(philos->dead_lock);
			break ;
		}
		(pthread_mutex_unlock(philos->dead_lock), pthread_mutex_lock(philos->meals));
		if (*philos->x >= philos->numofmeals * philos->numofphilo) {
			pthread_mutex_unlock(philos->meals);
			break ;
		}
		pthread_mutex_unlock(philos->meals);
		philos = philos->next;
	}
	while (i < numofphilo)
	{
		if (pthread_join(philos->thread, NULL))
			write(2, "pthread_detach failed\n", 28);
		(1) && (philos = philos->next, i++);
	}
}

void *routine_numofmeals(void *philo)
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
	if (t->philoindex % 2 == 1)
		usleep(200);
	while (t->numofmeals--)
	{
		if (ft_simulation(t))
			break ;
	}
	return (NULL);
}

void	ft_start_numofmeals(t_philo *philos, long numofphilo)
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
	while (1)
	{
		pthread_mutex_lock(philos->dead_flag);
		if (*philos->flag == 0)
		{
			pthread_mutex_unlock(philos->dead_flag);
			break ;
		}
		pthread_mutex_unlock(philos->dead_flag);
	}
	(monitor2(philos, numofphilo), destroy_mutex(philos));
}
