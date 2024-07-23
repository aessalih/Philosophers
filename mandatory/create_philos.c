#include "philo.h"

t_philo	*ft_circularlist(t_philo *list)
{
	t_philo	*head;

	head = list;
	while (head->next)
		head = head->next;
	head->next = list;
	return (head);
}

t_philo	*ft_philolist(t_philo *list, t_philo *node)
{
	t_philo	*head;
	int	i = 0;

	head = list;
	if (head == NULL && node == NULL)
		return (NULL);
	if (head == NULL)
		return (node);
	if (node == NULL)
		return (head);
	while (head->next)
		head = head->next;
	head->next = node;
	return (list);
}

t_philo	*ft_newnode(int	index, t_info *info)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (NULL);
	new->philoindex = index;
	new->philofork = 1;
	new->timetodie = info->timetodie;
	new->timetoeat = info->timetoeat;
	new->timetosleep = info->timetosleep;
	new->numofmeals = info->numofmeals;
	new->next = NULL;
	return (new);
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
		new = ft_newnode(i ,info);
		if (new == NULL)
			return (ft_free(philos), NULL);
		philos = ft_philolist(philos, new);
		i++;
	}
	philos = ft_circularlist(philos);
	return (philos);
}
