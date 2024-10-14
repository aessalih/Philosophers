/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:24:04 by aessalih          #+#    #+#             */
/*   Updated: 2024/10/07 09:25:33 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_circularlist(t_philo *list)
{
	t_philo	*head;

	head = list;
	while (head->next)
		head = head->next;
	head->next = list;
	list->previous = head;
	return (head);
}

t_philo	*ft_philolist(t_philo *list, t_philo *node)
{
	t_philo	*head;
	t_philo	*prev;

	head = list;
	prev = list;
	if (head == NULL && node == NULL)
		return (NULL);
	if (head == NULL)
		return (node);
	if (node == NULL)
		return (head);
	while (head->next)
		head = head->next;
	head->next = node;
	while (prev->next != node)
		prev = prev->next;
	node->previous = prev;
	return (list);
}

t_philo	*ft_newnode(int index, t_info *info)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (NULL);
	new->numofphilo = info->numofphilo;
	new->philoindex = index;
	new->philofork = 1;
	new->timetodie = info->timetodie;
	new->timetoeat = info->timetoeat;
	new->timetosleep = info->timetosleep;
	new->numofmeals = info->numofmeals;
	new->dead = &info->dead;
	new->wait = &info->waitphilo;
	new->flag = &info->flag;
	new->time = &info->time;
	new->x = &info->x;
	new->print_lock = info->lock;
	new->dead_lock = info->dead_lock;
	new->dead_flag = info->dead_flag;
	new->fork = malloc(sizeof(pthread_mutex_t));
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	ft_shareforks(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->numofphilo)
	{
		philo->next_fork = philo->next->fork;
		philo = philo->next;
		i++;
	}
}

t_philo	*create_philos(t_info *info)
{
	t_philo	*philos;
	t_philo	*new;
	int		i;

	i = 1;
	philos = NULL;
	while (i <= info->numofphilo)
	{
		new = ft_newnode(i, info);
		if (new == NULL)
			return (ft_free(philos), NULL);
		philos = ft_philolist(philos, new);
		i++;
	}
	philos = ft_circularlist(philos);
	ft_shareforks(philos);
	return (philos);
}
