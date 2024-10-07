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

void	ft_start_numofmeals(t_philo *philo, long numofphilo)
{
	int		i;

	initialize_mutex(philo);
	(1) && (i = 0, *philo->time = gettime());
	while (i < numofphilo)
	{
		if (pthread_create(&philo->thread, NULL, &routine_numofmeals, philo))
			perror("pthread_create function failed\n");
		(1) && (philo = philo->next, i++);
	}
	pthread_mutex_lock(philo->dead_lock);
	*philo->wait = 1;
	pthread_mutex_unlock(philo->dead_lock);
	// while (1)
	// {
	// 	pthread_mutex_lock(philo->dead_flag);
	// 	if (*philo->flag == 0)
	// 	{
	// 		pthread_mutex_unlock(philo->dead_flag);
	// 		break ;
	// 	}
	// 	pthread_mutex_unlock(philo->dead_flag);
	// }
	
	(monitor(philo, numofphilo), destroy_mutex(philo));
}
