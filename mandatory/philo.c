/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:28:28 by aessalih          #+#    #+#             */
/*   Updated: 2024/10/14 11:08:10 by aessalih         ###   ########.fr       */
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
	if (handle_input(info))
		return (0);
	philos = create_philos(info);
	if (philos == NULL)
		return (write(2, "malloc failed\n", 15), free(info), 1);
	if (ac == 5)
		ft_start(philos, info->numofphilo);
	else if (ac == 6)
		ft_start_numofmeals(philos, info->numofphilo);
	ft_free(philos);
	return (0);
}
