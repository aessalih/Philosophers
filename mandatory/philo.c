/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:28:28 by aessalih          #+#    #+#             */
/*   Updated: 2024/07/23 10:05:42 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_info	*info;
	int		istrue;

	philos = NULL;
	istrue = check_args(ac, av);
	if (istrue == 0)
		return (1);
	info = parse_args(ac, av);
	if (info == NULL)
		return (1);
	printf("info->numberofphilo: %ld\n", info->numofphilo);
	printf("info->timeToDie: %ld\n", info->timetodie);
	printf("info->timeToEat: %ld\n", info->timetoeat);
	printf("info->timeToSleep: %ld\n", info->timetosleep);
	if (ac == 6)
		printf("info->numOfMeals: %ld\n", info->numofmeals);
	philos = create_philos(av, info);
	if (philos == NULL)
		return (write(2, "malloc failed\n", 15), free(info), 1);
	return (0);
}
