/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:22:57 by aessalih          #+#    #+#             */
/*   Updated: 2024/08/19 17:08:09 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
// typedef struct s_philo
// {
// 	pthread_t		*thread;
// 	int				philoindex;
// 	int				dead;
// 	long			timetodie;
// 	long			timetoeat;
// 	long			timetosleep;
// 	long			numofmeals;
// 	pthread_mutex_t	*fork;
// 	pthread_mutex_t	*lock;
// 	struct s_philo	*next;
// 	struct s_philo	*previous;
// }	t_philo;


static void	initialize_mutex(t_philo *philo)
{
	t_philo	*tail;
	long	i;
	long	j;

	tail = philo;
	i = 0;
	j = philo->numofphilo;
	while (i < j)
	{
		philo->fork = malloc(sizeof(pthread_mutex_t));
		philo->lock = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo->fork, NULL);
		pthread_mutex_init(philo->lock, NULL);
		philo = philo->next;
		i++;
	}
}

// static void	destroy_mutex(t_philo *philo)
// {
// 	t_philo	*tail;

// 	tail = philo;
// 	if (pthread_mutex_destroy(tail->lock))
// 		perror("mutex_destroy failed 2\n");
// 	if (pthread_mutex_destroy(tail->fork))
// 		perror("mutex_destroy failed 1\n");
// 	tail = tail->next;
// 	while (tail != philo)
// 	{
// 		if (pthread_mutex_destroy(tail->lock))
// 			perror("destroy mutex failed 4\n");
// 		if (pthread_mutex_destroy(tail->fork))
// 			perror("destroy mutex failed 3\n");
// 		tail = tail->next;
// 	}
// }

void	ft_isdied(t_philo *t, double checktime)
{
	pthread_mutex_lock(t->lock);
	if ((gettime() - checktime) > (double)t->timetodie)
	{
		*(t->dead) = t->philoindex;
		printf("%d is died\n", t->philoindex);
	}
	pthread_mutex_unlock(t->lock);
}

void	custom_print(t_philo *t, double time, int flag)
{
	pthread_mutex_lock(t->lock);
	if (flag == FORK)
		printf("%zu %d has taken a fork\n", (size_t)(gettime() - time), t->philoindex);
	else if (flag == EAT)
		printf("%zu %d is eating\n", (size_t)(gettime() - time), t->philoindex);
	else if (flag == SLEEP)
		printf("%zu %d is sleeping\n", (size_t)(gettime() - time), t->philoindex);
	else if (flag == THINK)
		printf("%zu %d is thinking\n", (size_t)(gettime() - time), t->philoindex);
	pthread_mutex_unlock(t->lock);
}

void	*routine(void *philo)
{
	t_philo	*t;

	t = (t_philo*)philo;
	////////////////////
	// ALL THE PHILOS //
	////////////////////
	t->time = gettime();
	t->lastmeal = gettime();
	while (1)
	{
		// pthread_mutex_lock(t->lock);
		// printf("%zu ms | index : %d\n", (size_t)gettime(), t->philoindex);
		// pthread_mutex_unlock(t->lock);
		ft_think(t, t->time);
		pthread_mutex_lock(t->fork);
		// pthread_mutex_lock(t->lock);
		// printf("%zu ms | index : %d\n", (size_t)gettime(), t->philoindex);
		// pthread_mutex_unlock(t->lock);
		custom_print(t, t->time, FORK);
		pthread_mutex_lock(t->next->fork);
		t->lastmeal = gettime();
		custom_print(t, t->time, FORK);
		ft_eat(t, t->time);
		// pthread_mutex_lock(t->lock);
		// printf("%zu ms | index : %d\n", (size_t)gettime(), t->philoindex);
		// pthread_mutex_unlock(t->lock);
		pthread_mutex_unlock(t->fork);
		pthread_mutex_unlock(t->next->fork);
		ft_print_sleep(t, t->time);
		// pthread_mutex_lock(t->lock);
		// printf("%zu ms | index : %d\n", (size_t)gettime(), t->philoindex);
		// pthread_mutex_unlock(t->lock);
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
		ft_isdied(philos, philos->time);
		if (*philos->dead != 0)
			break ;
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
	monitor(philos, numofphilo);
	// destroy_mutex(philos);
}
