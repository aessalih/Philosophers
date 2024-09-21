#include "philo.h"

int	ft_think(t_philo *t, long time)
{
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0) {
		pthread_mutex_unlock(t->dead_lock);
		pthread_mutex_unlock(t->dead_flag);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	custom_print(t, time, THINK);
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0) {
		pthread_mutex_unlock(t->dead_lock);
		pthread_mutex_unlock(t->dead_flag);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	return (0);
}

int	ft_eat(t_philo *t, long time)
{
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0) {
		pthread_mutex_unlock(t->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	custom_print(t, time, EAT);
	ft_sleep(t->timetoeat);
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0) {
		pthread_mutex_unlock(t->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	return (0);
}

int	ft_print_sleep(t_philo *t, long time)
{
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0) {
		pthread_mutex_unlock(t->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	custom_print(t, time, SLEEP);
	ft_sleep(t->timetosleep);
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0) {
		pthread_mutex_unlock(t->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	return (0);
}

int	ft_simulation(t_philo *t)
{
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0)
		return (pthread_mutex_unlock(t->dead_lock), 1);
	pthread_mutex_unlock(t->dead_lock);
	if (ft_think(t, *t->time)){
		return (1);
	}
	pthread_mutex_lock(t->fork);
	custom_print(t, *t->time, FORK);
	pthread_mutex_lock(t->next_fork);
	custom_print(t, *t->time, FORK);
	pthread_mutex_lock(t->dead_flag);
	t->lastmeal = gettime();
	pthread_mutex_unlock(t->dead_flag);
	if (ft_eat(t, *t->time)){
		return (1); 
	}
	pthread_mutex_unlock(t->fork);
	pthread_mutex_unlock(t->next_fork);
	if (ft_print_sleep(t, *t->time)) {
		return (1);
	}
	return (0);
}
