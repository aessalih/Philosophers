/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:24:24 by aessalih          #+#    #+#             */
/*   Updated: 2024/10/07 09:27:02 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL))
	{
		write(2, "gettimeofday failed\n", 21);
		return (0);
	}
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	ft_sleep(long timetosleep)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL))
	{
		write(2, "gettimeofday failed\n", 21);
		return (1);
	}
	time = gettime();
	while ((gettime() - time) < timetosleep)
		usleep(100);
	return (0);
}
