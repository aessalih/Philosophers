/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:46:28 by aessalih          #+#    #+#             */
/*   Updated: 2024/10/07 08:47:15 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_mutex(t_philo *philo)
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
