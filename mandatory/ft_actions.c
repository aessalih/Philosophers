#include "philo.h"

void	ft_think(t_philo *t, double time)
{
	pthread_mutex_lock(&t->lock);
	printf("%zu, %d is thinking\n", (size_t)(gettime() - time), t->philoindex);
	pthread_mutex_unlock(&t->lock);
}

void	ft_eat(t_philo *t, double time)
{
	pthread_mutex_lock(&t->fork);
	pthread_mutex_lock(&t->next->fork);
	pthread_mutex_lock(&t->lock);
	printf("%zu, %d is eating\n", (size_t)(gettime() - time), t->philoindex);
	pthread_mutex_unlock(&t->lock);
	ft_sleep(t->timetoeat);
	pthread_mutex_unlock(&t->fork);
	pthread_mutex_unlock(&t->next->fork);
}

void	ft_print_sleep(t_philo *t, double time)
{
	pthread_mutex_lock(&t->lock);
	printf("%zu, %d is sleeping\n", (size_t)(gettime() - time), t->philoindex);
	pthread_mutex_unlock(&t->lock);
}