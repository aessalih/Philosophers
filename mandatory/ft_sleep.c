#include "philo.h"

double	gettime()
{
	struct timeval	tv;
	double			time;

	if (gettimeofday(&tv, NULL))
	{
		write(2, "gettimeofday failed\n", 21);
		return (0);
	}
	time = (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
	return (time);
}

int	ft_sleep(long timetosleep)
{
	struct timeval	tv;
	double	time;

	if (gettimeofday(&tv, NULL))
	{
		write(2, "gettimeofday failed\n", 21);
		return (1);
	}
	time = gettime();
	while ((gettime() - time) < timetosleep)
		;
	return (0);
}

// int	main()
// {
// 	int i = ft_sleep(10000);
// 	return (0);
// }