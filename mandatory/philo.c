/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:28:28 by aessalih          #+#    #+#             */
/*   Updated: 2024/08/04 19:31:51 by aessalih         ###   ########.fr       */
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
	philos = create_philos(info);
	if (philos == NULL)
		return (write(2, "malloc failed\n", 15), free(info), 1);
	t_philo	*t;
	t = philos;
	printf("index: %d | address: %p\n\n", t->philoindex, t);
	t = t->next;
	while (t != philos)
	{
		printf("index: %d | address: %p\n\n", t->philoindex, t);
		t = t->next;
	}
	ft_start(philos, info->numofphilo);
	ft_free(philos);
	return (0);
}
