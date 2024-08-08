#include "philo.h"

void	ft_free(t_philo *philo)
{
	t_philo	*head;
	t_philo	*tail;

	tail = philo;
	head = tail->next;
	philo = philo->next;
	while (philo != tail)
	{
		free(head);
		philo = philo->next;
		head = philo;
	}
	free(tail);
}
