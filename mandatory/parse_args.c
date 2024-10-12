/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:49:05 by aessalih          #+#    #+#             */
/*   Updated: 2024/09/03 10:43:24 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	n;
	int		j;

	i = 0;
	j = 1;
	n = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			j = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i++] - '0');
		if ((n > INT_MAX && j == 1) || (n < INT_MIN && j == -1))
			(write(2, "Please enter integers\n", 23), exit (1));
	}
	if ((str[0] == '-' || str[0] == '+') && str[1] == '\0')
		(write(2, "Please enter integers\n", 23), exit (1));
	return (j * n);
}

t_info	*parse_args(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->numofphilo = ft_atoi(av[1]);
	info->timetodie = ft_atoi(av[2]);
	info->timetoeat = ft_atoi(av[3]);
	info->timetosleep = ft_atoi(av[4]);
	if (ac == 6)
		info->numofmeals = ft_atoi(av[5]);
	else
		info->numofmeals = 0;
	if (info->numofmeals < 0 || info->numofphilo <= 0)
		return (write(2, "Please enter postive integers\n", 31),
			free(info), NULL);
	if (info->timetodie <= 0 || info->timetoeat <= 0 || info->timetosleep <= 0)
		return (write(2, "Please enter postive integers\n", 31),
			free(info), NULL);
	info->dead = 0;
	info->waitphilo = 0;
	info->time = gettime();
	info->lock = malloc(sizeof(pthread_mutex_t));
	info->dead_lock = malloc(sizeof(pthread_mutex_t));
	info->dead_flag = malloc(sizeof(pthread_mutex_t));
	return (info);
}
