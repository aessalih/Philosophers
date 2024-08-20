#include "philo.h"

void	ft_think(t_philo *t, double time)
{
	custom_print(t, time, THINK);
}

void	ft_eat(t_philo *t, double time)
{
	custom_print(t, time, EAT);
	ft_sleep(t->timetoeat);
}

void	ft_print_sleep(t_philo *t, double time)
{
	custom_print(t, time, SLEEP);
	ft_sleep(t->timetosleep);
}