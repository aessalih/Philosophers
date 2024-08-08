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

	tail = philo;
	pthread_mutex_init(&(tail->fork), NULL);
	pthread_mutex_init(&(tail->lock), NULL);
	while (tail != philo)
	{
		printf("here\n");
		// printf("pilo index: %d\n", tail->philoindex);
		pthread_mutex_init(&(tail->fork), NULL);
		printf("here\n\n");
		pthread_mutex_init(&(tail->lock), NULL);
		// printf("tail->next: %d\n", tail->next->philoindex);
		tail = tail->next;
	}
}

static void	destroy_mutex(t_philo *philo)
{
	t_philo	*head;
	t_philo	*tail;

	head = philo->next;
	tail = philo;
	int i = 0;
		printf("i: %d\n", i++);
	while (head != tail)
	{
		pthread_mutex_unlock(&(head->fork));
		if (pthread_mutex_destroy(&(head->fork)))
			perror("destroy mutex failed\n");
		printf("i: %d\n", i++);
		pthread_mutex_destroy(&(head->lock));
		head = head->next;
		printf("i: %d\n", i++);
	}
		printf("i: %d\n", i++);
	pthread_mutex_destroy(&(head->fork));
		printf("i: %d\n", i++);
	pthread_mutex_destroy(&(head->lock));
		printf("i: %d\n", i++);
}

void	*routine(void *philo)
{
	t_philo	*t;

	t = (t_philo*)philo;
	// pthread_mutex_lock(&t->philofork);
	for (int i = 0; i < 1000; i++)
		j++;
	// pthread_mutex_unlock(&t->philofork);
	return (NULL);
}

void	ft_start(t_philo *philos, long numofphilo)
{
	int		i;
	int		j = 0;

	i = 0;
	initialize_mutex(philos);
	while (i < numofphilo)
	{
		if (pthread_create(&philos->thread, NULL, &routine, &philos))
			perror("pthread_create function failed\n");
		philos = philos->next;
		i++;
	}
	i = 0;
	while (i < numofphilo)
	{
		if (pthread_join(philos->thread, NULL))
			perror("pthread_join failed\n");
		philos = philos->next;
		i++;
	}
	printf("j = %d\n", j);
	destroy_mutex(philos);
}
