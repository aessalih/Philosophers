#include "philo.h"

void	ft_free(t_philo *philo)
{
	t_philo	*head;

	head = philo;
	while (philo)
	{
		free(head);
		philo = philo->next;
		head = philo;
	}
}
