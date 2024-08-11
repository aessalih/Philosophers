/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:22:57 by aessalih          #+#    #+#             */
/*   Updated: 2024/08/04 19:34:34 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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

int	j = 0;

static void	initialize_mutex(t_philo *philo)
{
	t_philo	*tail;
	long	i;
	long	j;

	tail = philo;
	i = 0;
	j = philo->numofphilo;
	// printf("philonumber: %ld\n", philo->numofphilo);
	// philo = philo->next;
	// while (philo != tail)
	// {
	// 	printf("philonumber: %ld\n", philo->numofphilo);
	// 	philo = philo->next;
	// }
	while (i < j)
	{
		// printf("-------> %p\n", philo);
		philo->fork = malloc(sizeof(pthread_mutex_t));
		philo->lock = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo->fork, NULL);
		pthread_mutex_init(philo->lock, NULL);
		philo = philo->next;
		i++;
		// printf("%d\n", philo->numofphilo);
	}
}

static void	destroy_mutex(t_philo *philo)
{
	t_philo	*tail;

	tail = philo;
	if (pthread_mutex_destroy(tail->lock))
		perror("mutex_destroy failed 2\n");
	if (pthread_mutex_destroy(tail->fork))
		perror("mutex_destroy failed 1\n");
	tail = tail->next;
	while (tail != philo)
	{
		if (pthread_mutex_destroy(tail->lock))
			perror("destroy mutex failed 4\n");
		if (pthread_mutex_destroy(tail->fork))
			perror("destroy mutex failed 3\n");
		tail = tail->next;
	}
}

void	*routine(void *philo)
{
	t_philo	*t;

	t = (t_philo*)philo;
	pthread_mutex_lock(t->fork);
	for (int i = 0; i < 10000; i++)
		j++;
	pthread_mutex_unlock(t->fork);
	return (NULL);
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
	i = 0;
	while (i < numofphilo)
	{
		if (pthread_join(philos->thread, NULL) != 0)
		{
			printf("join value: %d\n\n\n", pthread_join(philos->thread, NULL));
			perror("pthread_join failed\n");
		}
		philos = philos->next;
		i++;
	}
	printf("j = %d\n", j);
	destroy_mutex(philos);
}
