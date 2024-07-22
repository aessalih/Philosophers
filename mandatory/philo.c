/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessalih <aessalih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:28:28 by aessalih          #+#    #+#             */
/*   Updated: 2024/07/21 11:39:16 by aessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_info	*info;

	philos = NULL;
	check_args(ac, av);
	parse_args(ac, av, info);
	printf("I wad here3\n");
	// philos = create_philos(av);
	printf("I wad here4\n");
	return (0);
}
