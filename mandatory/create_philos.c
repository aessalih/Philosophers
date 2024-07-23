#include "philo.h"

t_philo	*ft_newnode(int	index)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (NULL);
	new->philoindex = index;
	new->philofork = 1;
	return (new);
}

t_philo	*create_philos(char **av, t_info *info)
{
	t_philo	*philos;
	int		i;

	i = 1;
	while (av[i])
	{
		
		i++;
	}
	return (philos);
}
