/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:40:02 by aessalih          #+#    #+#             */
/*   Updated: 2024/10/14 13:42:35 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_input(t_info *info)
{
	if (info->numofphilo == 1)
	{
		printf("0 1 is thinking\n");
		printf("0 1 has taken a fork\n");
		ft_sleep(info->timetodie);
		printf("%ld 1 is died\n", info->timetodie);
		return (1);
	}
	return (0);
}

static int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] <= 47 || s[i] >= 58)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		write(2, "Please enter right arguments:\n\n\n", 33);
		write(2, "\t<numberOfPhilosophers>\n\t<timeToDie>\n\t<TimeToEat>", 50);
		write(2, "\n\t<timeToSleep>\n\t<numberOfTimesMustEat(optional)>\n\n",
			52);
		return (0);
	}
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
		{
			write(2, "Please enter integer arguments\n", 32);
			return (0);
		}
		i++;
	}
	return (1);
}
