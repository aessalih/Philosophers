#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	n;
	long	k;
	int		j;

	i = 0;
	j = 1;
	n = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			j = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		k = n;
		n = n * 10 + (str[i++] - '0');
		if ((n > INT_MAX && j == 1) || (n < INT_MIN && j == -1))
			(write(2, "Please enter integers\n", 23), exit (1));
	}
	if ((str[0] == '-' || str[0] == '+') && str[1] == '\0')
		(write(2, "Please enter integers\n", 23), exit (1));
	return (j * n);
}


void	parse_args(int ac, char **av, t_info *info)
{
	if (ac == 5)
	{
		printf("I was here1\n");
		info->numOfphilo = ft_atoi(av[1]);
		info->timeToDie = ft_atoi(av[2]);
		info->timeToEat = ft_atoi(av[3]);
		info->timeToSleep = ft_atoi(av[4]);
		if (info->numOfphilo <= 0 || info->timeToSleep <= 0)
			(write(2, "Please enter postive integers\n", 31), exit (1));
		if (info->timeToDie <= 0 || info->timeToEat <= 0)
			(write(2, "Please enter postive integers\n", 31), exit (1));
		printf("I was here2\n");
	}
	else
	{
		info->numOfphilo = ft_atoi(av[1]);
		info->timeToDie = ft_atoi(av[2]);
		info->timeToEat = ft_atoi(av[3]);
		info->timeToSleep = ft_atoi(av[4]);
		info->numOfMeals = ft_atoi(av[5]);
		if (info->numOfMeals <= 0 || info->numOfphilo <= 0)
			(write(2, "Please enter postive integers\n", 31), exit (1));
		if (info->timeToDie <= 0 || info->timeToEat <= 0 || info->timeToSleep <= 0)
			(write(2, "Please enter postive integers\n", 31), exit (1));
	}
}
