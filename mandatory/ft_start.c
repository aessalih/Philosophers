/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:22:57 by aessalih          #+#    #+#             */
/*   Updated: 2024/09/03 11:00:09 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>

static void	initialize_mutex(t_philo *philo)
{
	t_philo	*tail;
	long	i;
	long	j;

	tail = philo;
	i = 0;
	j = philo->numofphilo;
	pthread_mutex_init(philo->print_lock, NULL);
	pthread_mutex_init(philo->dead_lock, NULL);
	pthread_mutex_init(philo->dead_flag, NULL);
	while (i < j)
	{
		pthread_mutex_init(philo->fork, NULL);
		philo = philo->next;
		i++;
	}
}

void	destroy_mutex(t_philo *philo)
{
	t_philo	*tail;

	tail = philo;
	pthread_mutex_destroy(tail->print_lock);
	pthread_mutex_destroy(tail->dead_lock);
	pthread_mutex_destroy(tail->dead_flag);
	pthread_mutex_destroy(tail->fork);
	tail = tail->next;
	while (tail != philo)
	{
		pthread_mutex_destroy(tail->fork);
		tail = tail->next;
	}
}

void	ft_isdied(t_philo *t, double *checktime)
{
	pthread_mutex_lock(t->dead_flag);
	if ((gettime() - *checktime) > (double)t->timetodie)
	{
		pthread_mutex_lock(t->dead_lock);
		*t->dead = t->philoindex;
		pthread_mutex_unlock(t->dead_lock);
		pthread_mutex_lock(t->print_lock);
		printf("%zu %d is died\n", (size_t)(gettime() - t->time), t->philoindex);
		pthread_mutex_unlock(t->print_lock);
	}
	pthread_mutex_unlock(t->dead_flag);
}

void	custom_print(t_philo *t, double time, int flag)
{
	pthread_mutex_lock(t->print_lock);
	if (flag == FORK)
		printf("%zu %d has taken a fork\n", ((size_t)gettime() - (size_t)time), t->philoindex);
	else if (flag == EAT)
		printf("%zu %d is eating\n", ((size_t)gettime() - (size_t)time), t->philoindex);
	else if (flag == SLEEP)
		printf("%zu %d is sleeping\n", ((size_t)gettime() - (size_t)time), t->philoindex);
	else if (flag == THINK)
		printf("%zu %d is thinking\n", ((size_t)gettime() - (size_t)time), t->philoindex);
	pthread_mutex_unlock(t->print_lock);
}

void	*routine(void *philo)
{
	t_philo	*t;

	t = (t_philo*)philo;
	while (1) {
		pthread_mutex_lock(t->dead_lock);
		if (*t->wait != 0)
		{
			pthread_mutex_unlock(t->dead_lock);
			break ;
		}
		pthread_mutex_unlock(t->dead_lock);
	}
	pthread_mutex_lock(t->dead_flag);
	t->time = gettime();
	t->lastmeal = gettime();
	pthread_mutex_unlock(t->dead_flag);
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
	while (i < numofphilo)
	{
		if (pthread_detach(philos->thread))
			write(2, "pthread_detach failed\n", 28);
		philos = philos->next;
		i++;
	}
	while (1)
	{
		// pthread_mutex_lock(philos->dead_lock);
		ft_isdied(philos, &philos->lastmeal);
		// pthread_mutex_unlock(philos->dead_lock);
		pthread_mutex_lock(philos->dead_lock);
		if (*philos->dead != 0) {
			pthread_mutex_unlock(philos->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philos->dead_lock);
		philos = philos->next;
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
		philos = philos->next;
		i++;
	}
	pthread_mutex_lock(philos->dead_lock);
	*philos->wait = 1;
	pthread_mutex_unlock(philos->dead_lock);
	monitor(philos, numofphilo);
	destroy_mutex(philos);
}
