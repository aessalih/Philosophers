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

void	ft_isdied(t_philo *t, double checktime)
{
	if ((gettime() - checktime) > (double)t->timetodie)
	{
		t->dead = t->philoindex;
		usleep(100);
	}

}

void	*routine(void *philo)
{
	t_philo	*t;
	double	time;
	double	checktime;

	t = (t_philo*)philo;
	time = gettime();
	checktime = gettime();
	// usleep(10);
	while (1)
	{
		ft_isdied(t, checktime);
		ft_think(t, time);
		ft_isdied(t, checktime);
		pthread_mutex_lock(&t->lock);
		printf("%zu, %d has taken a fork\n", (size_t)(gettime() - time), t->philoindex);
		pthread_mutex_unlock(&t->lock);
		pthread_mutex_lock(&t->lock);
		printf("%zu, %d has taken a fork\n", (size_t)(gettime() - time), t->philoindex);
		pthread_mutex_unlock(&t->lock);
		if ((gettime() - checktime) > (double)t->timetodie)
			t->dead = 1;
		ft_eat(t, time);
		checktime = gettime();
		ft_print_sleep(t, time);
		ft_sleep(t->timetosleep);
		ft_isdied(t, checktime);
	}
	return (NULL);
}

void	monitor(t_philo *philos, int *dead, long numofphilo)
{
	int	i;

	i = 0;
	while (philos->dead == 0)
		philos = philos->next;
	printf("\n\n\n\n\n\n%d is died\n\n\n\n\n\n", philos->dead);
	while (i < numofphilo)
	{
		pthread_detach(philos->thread);
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
		philos = philos->next;
		i++;
	}
	monitor(philos, &philos->dead, numofphilo);
	i = 0;
	// while (i < numofphilo)
	// {
	// 	if (pthread_join(philos->thread, NULL) != 0)
	// 	{
	// 		printf("join value: %d\n\n\n", pthread_join(philos->thread, NULL));
	// 		perror("pthread_join failed\n");
	// 	}
	// 	philos = philos->next;
	// 	i++;
	// }
	destroy_mutex(philos);
}
