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

int	j = 0;

void	*routine(void *arg)
{
	j += 1;
	printf("j = %d\n", j);
	return (NULL);
}

void	ft_start(t_philo *philos, long numofphilo)
{
	int		i;

	i = 0;
	while (i < numofphilo)
	{
		if (pthread_create(&philos->thread, NULL, &routine, NULL))
			perror("pthread_create function failed\n");
		philos = philos->next;
		i++;
	}
	i = 0;
	while (i < numofphilo)
	{
		if (pthread_join(philos->thread, NULL))
			perror("pthread_join failed\n");
		i++;
	}
}
