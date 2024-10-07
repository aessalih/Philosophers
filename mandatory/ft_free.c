/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:24:18 by aessalih          #+#    #+#             */
/*   Updated: 2024/10/07 09:24:19 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *philo)
{
	t_philo	*head;
	t_philo	*tail;

	tail = philo;
	head = tail->next;
	philo = philo->next;
	while (philo != tail)
	{
		free(head);
		philo = philo->next;
		head = philo;
	}
	free(tail);
}
