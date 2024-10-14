# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/_pthread/_pthread_mutex_t.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DEATH 0

typedef struct s_philo
{
	pthread_t		thread;
	int				philoindex;
	int				philofork;
	int				*dead;
	long			numofphilo;
	long			timetodie;
	long			timetoeat;
	long			timetosleep;
	long			numofmeals;
	long			lastmeal;
	long			*time;
	int				*wait;
	int				*flag;
	long			*x;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*dead_flag;
	pthread_mutex_t	*meals;
	struct s_philo	*next;
	struct s_philo	*previous;
}	t_philo;

typedef struct s_info
{
	long			numofphilo;
	long			timetodie;
	long			timetoeat;
	long			timetosleep;
	long			numofmeals;
	long			time;
	int				flag;
	long			x;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*dead_flag;
	pthread_mutex_t	*meals;
	int				dead;
	int				waitphilo;
}	t_info;

static int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] <= 47 || s[i] >= 58)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		write(2, "Please enter right arguments:\n\n\n", 33);
		write(2, "\t<numberOfPhilosophers>\n\t<timeToDie>\n\t<TimeToEat>", 50);
		write(2, "\n\t<timeToSleep>\n\t<numberOfTimesMustEat(optional)>\n\n",
			52);
		return (0);
	}
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
		{
			write(2, "Please enter integer arguments\n", 32);
			return (0);
		}
		i++;
	}
	return (1);
}


t_philo	*ft_circularlist(t_philo *list)
{
	t_philo	*head;

	head = list;
	while (head->next)
		head = head->next;
	head->next = list;
	list->previous = head;
	return (head);
}

t_philo	*ft_philolist(t_philo *list, t_philo *node)
{
	t_philo	*head;
	t_philo	*prev;

	head = list;
	prev = list;
	if (head == NULL && node == NULL)
		return (NULL);
	if (head == NULL)
		return (node);
	if (node == NULL)
		return (head);
	while (head->next)
		head = head->next;
	head->next = node;
	while (prev->next != node)
		prev = prev->next;
	node->previous = prev;
	return (list);
}

t_philo	*ft_newnode(int index, t_info *info)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (NULL);
	new->numofphilo = info->numofphilo;
	new->philoindex = index;
	new->philofork = 1;
	new->timetodie = info->timetodie;
	new->timetoeat = info->timetoeat;
	new->timetosleep = info->timetosleep;
	new->numofmeals = info->numofmeals;
	new->dead = &info->dead;
	new->wait = &info->waitphilo;
	new->flag = &info->flag;
	new->time = &info->time;
	new->x = &info->x;
	new->print_lock = info->lock;
	new->dead_lock = info->dead_lock;
	new->dead_flag = info->dead_flag;
	new->meals = info->meals;
	new->fork = malloc(sizeof(pthread_mutex_t));
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	ft_shareforks(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->numofphilo)
	{
		philo->next_fork = philo->next->fork;
		philo = philo->next;
		i++;
	}
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
		new = ft_newnode(i, info);
		if (new == NULL)
			return (ft_free(philos), NULL);
		philos = ft_philolist(philos, new);
		i++;
	}
	philos = ft_circularlist(philos);
	ft_shareforks(philos);
	return (philos);
}


int	ft_think(t_philo *t, long time)
{
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0)
	{
		pthread_mutex_unlock(t->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	custom_print(t, time, THINK);
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0)
	{
		pthread_mutex_unlock(t->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	return (0);
}

int	ft_eat(t_philo *t, long time)
{
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0)
	{
		pthread_mutex_unlock(t->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	custom_print(t, time, EAT);
	ft_sleep(t->timetoeat);
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0)
	{
		pthread_mutex_unlock(t->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	return (0);
}

int	ft_print_sleep(t_philo *t, long time)
{
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0)
	{
		pthread_mutex_unlock(t->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(t->dead_lock);
	custom_print(t, time, SLEEP);
	ft_sleep(t->timetosleep);
	pthread_mutex_lock(t->dead_lock);
	if (*t->dead != 0)
	{
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
	if (ft_think(t, *t->time))
		return (1);
	pthread_mutex_lock(t->fork);
	custom_print(t, *t->time, FORK);
	pthread_mutex_lock(t->next_fork);
	custom_print(t, *t->time, FORK);
	pthread_mutex_lock(t->dead_flag);
	t->lastmeal = gettime();
	pthread_mutex_unlock(t->dead_flag);
	if (ft_eat(t, *t->time))
	{
		pthread_mutex_unlock(t->fork);
		pthread_mutex_unlock(t->next_fork);
		return (1);
	}
	pthread_mutex_unlock(t->fork);
	pthread_mutex_unlock(t->next_fork);
	if (ft_print_sleep(t, *t->time))
		return (1);
	return (0);
}


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


void	initialize_mutex(t_philo *philo)
{
	long	i;
	long	j;

	i = 0;
	j = philo->numofphilo;
	pthread_mutex_init(philo->print_lock, NULL);
	pthread_mutex_init(philo->dead_lock, NULL);
	pthread_mutex_init(philo->dead_flag, NULL);
	pthread_mutex_init(philo->meals, NULL);
	while (i < j)
	{
		pthread_mutex_init(philo->fork, NULL);
		philo = philo->next;
		i++;
	}
}

void	destroy_mutex(t_philo *philo)
{
	t_philo	*tail;

	tail = philo;
	pthread_mutex_destroy(tail->print_lock);
	pthread_mutex_destroy(tail->dead_lock);
	pthread_mutex_destroy(tail->dead_flag);
	pthread_mutex_destroy(tail->meals);
	pthread_mutex_destroy(tail->fork);
	tail = tail->next;
	while (tail != philo)
	{
		pthread_mutex_destroy(tail->fork);
		tail = tail->next;
	}
}


void	ft_isdied(t_philo *t, long *checktime)
{
	pthread_mutex_lock(t->dead_flag);
	if ((gettime() - *checktime) > t->timetodie)
	{
		pthread_mutex_lock(t->dead_lock);
		*t->dead = t->philoindex;
		pthread_mutex_unlock(t->dead_lock);
		custom_print(t, *checktime, DEATH);
	}
	pthread_mutex_unlock(t->dead_flag);
}
long	gettime(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL))
	{
		write(2, "gettimeofday failed\n", 21);
		return (0);
	}
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	ft_sleep(long timetosleep)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL))
	{
		write(2, "gettimeofday failed\n", 21);
		return (1);
	}
	time = gettime();
	while ((gettime() - time) < timetosleep)
		usleep(100);
	return (0);
}


void	custom_print(t_philo *t, long time, int flag)
{
	pthread_mutex_lock(t->print_lock);
	if (flag == DEATH)
		printf("%ld %d is died\n", (gettime() - time), t->philoindex);
	pthread_mutex_lock(t->dead_lock);
	if (flag == FORK && *t->dead == 0)
		printf("%ld %d has taken a fork\n", (gettime() - time), t->philoindex);
	else if (flag == EAT && *t->dead == 0)
		printf("%ld %d is eating\n", (gettime() - time), t->philoindex);
	else if (flag == SLEEP && *t->dead == 0)
		printf("%ld %d is sleeping\n", (gettime() - time), t->philoindex);
	else if (flag == THINK && *t->dead == 0)
		printf("%ld %d is thinking\n", (gettime() - time), t->philoindex);
	pthread_mutex_unlock(t->dead_lock);
	pthread_mutex_unlock(t->print_lock);
}

void	*routine(void *philo)
{
	t_philo	*t;

	t = (t_philo *)philo;
	pthread_mutex_lock(t->dead_flag);
	t->lastmeal = gettime();
	pthread_mutex_unlock(t->dead_flag);
	while (1)
	{
		pthread_mutex_lock(t->dead_lock);
		if (*t->wait != 0)
		{
			pthread_mutex_unlock(t->dead_lock);
			break ;
		}
		pthread_mutex_unlock(t->dead_lock);
	}
	if (t->philoindex % 2 == 1)
		usleep(200);
	while (1)
	{
		if (ft_simulation(t))
			break ;
	}
	return (NULL);
}

void	monitor(t_philo *philos, long numofphilo)
{
	int	i;

	i = 0;
	while (1)
	{
		ft_isdied(philos, &philos->lastmeal);
		pthread_mutex_lock(philos->dead_lock);
		if (*philos->dead != 0)
		{
			pthread_mutex_unlock(philos->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philos->dead_lock);
		philos = philos->next;
	}
	i = 0;
	while (i < numofphilo)
	{
		if (pthread_join(philos->thread, NULL))
			write(2, "pthread_detach failed\n", 28);
		philos = philos->next;
		i++;
	}
}

void	monitor2(t_philo *philos, long numofphilo, int philo_number)
{
	int	i;

	i = 0;
	while (1)
	{
		(ft_isdied(philos, &philos->lastmeal), pthread_mutex_lock(philos->dead_lock));
		if (*philos->dead != 0)
		{
			pthread_mutex_unlock(philos->dead_lock);
			break ;
		}
		(pthread_mutex_unlock(philos->dead_lock), pthread_mutex_lock(philos->meals));
		if (*philos->x >= philos->numofmeals * philo_number) {
			pthread_mutex_unlock(philos->meals);
			break ;
		}
		pthread_mutex_unlock(philos->meals);
		philos = philos->next;
	}
	while (i < numofphilo)
	{
		if (pthread_join(philos->thread, NULL))
			write(2, "pthread_detach failed\n", 28);
		(1) && (philos = philos->next, i++);
	}
}

void *routine_numofmeals(void *philo)
{
	t_philo	*t;

	t = (t_philo *)philo;
	pthread_mutex_lock(t->dead_flag);
	t->lastmeal = gettime();
	pthread_mutex_unlock(t->dead_flag);
	while (1)
	{
		pthread_mutex_lock(t->dead_lock);
		if (*t->wait != 0)
		{
			pthread_mutex_unlock(t->dead_lock);
			break ;
		}
		pthread_mutex_unlock(t->dead_lock);
	}
	if (t->philoindex % 2 == 1)
		usleep(200);
	while (1)
	{
		if (ft_simulation(t))
			break ;
		pthread_mutex_lock(t->meals);
		(*t->x)++;
		if (--t->numofmeals == 0) {
			pthread_mutex_unlock(t->meals);
			break ;
		}
		pthread_mutex_unlock(t->meals);
	}
	return (NULL);
}

void	ft_start_numofmeals(t_philo *philos, long numofphilo)
{
	int		i;

	initialize_mutex(philos);
	i = 0;
	while (i < numofphilo)
	{
		if (pthread_create(&philos->thread, NULL, &routine_numofmeals, philos))
			perror("pthread_create function failed\n");
		(1) && (philos = philos->next, i++);
	}
	*philos->time = gettime();
	pthread_mutex_lock(philos->dead_lock);
	*philos->wait = 1;
	pthread_mutex_unlock(philos->dead_lock);
	while (1)
	{
		pthread_mutex_lock(philos->dead_flag);
		if (*philos->flag == 0)
		{
			pthread_mutex_unlock(philos->dead_flag);
			break ;
		}
		pthread_mutex_unlock(philos->dead_flag);
	}
	(monitor2(philos, numofphilo, i), destroy_mutex(philos));
}


void	ft_start(t_philo *philos, long numofphilo)
{
	int		i;

	initialize_mutex(philos);
	i = 0;
	while (i < numofphilo)
	{
		if (pthread_create(&philos->thread, NULL, &routine, philos))
			perror("pthread_create function failed\n");
		(1) && (philos = philos->next, i++);
	}
	*philos->time = gettime();
	pthread_mutex_lock(philos->dead_lock);
	*philos->wait = 1;
	pthread_mutex_unlock(philos->dead_lock);
	while (1)
	{
		pthread_mutex_lock(philos->dead_flag);
		if (*philos->flag == 0)
		{
			pthread_mutex_unlock(philos->dead_flag);
			break ;
		}
		pthread_mutex_unlock(philos->dead_flag);
	}
	(monitor(philos, numofphilo), destroy_mutex(philos));
}


long	ft_atoi(const char *str)
{
	int		i;
	long	n;
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
		n = n * 10 + (str[i++] - '0');
		if ((n > INT_MAX && j == 1) || (n < INT_MIN && j == -1))
			(write(2, "Please enter integers\n", 23), exit (1));
	}
	if ((str[0] == '-' || str[0] == '+') && str[1] == '\0')
		(write(2, "Please enter integers\n", 23), exit (1));
	return (j * n);
}

t_info	*parse_args(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->numofphilo = ft_atoi(av[1]);
	info->timetodie = ft_atoi(av[2]);
	info->timetoeat = ft_atoi(av[3]);
	info->timetosleep = ft_atoi(av[4]);
	if (ac == 6)
		info->numofmeals = ft_atoi(av[5]);
	else
		info->numofmeals = 0;
	if (info->numofmeals < 0 || info->numofphilo <= 0)
		return (write(2, "Please enter postive integers\n", 31),
			free(info), NULL);
	if (info->timetodie <= 0 || info->timetoeat <= 0 || info->timetosleep <= 0)
		return (write(2, "Please enter postive integers\n", 31),
			free(info), NULL);
	(1) && (info->dead = 0, info->waitphilo = 0, info->x = 0);
	info->time = gettime();
	info->lock = malloc(sizeof(pthread_mutex_t));
	info->dead_lock = malloc(sizeof(pthread_mutex_t));
	info->dead_flag = malloc(sizeof(pthread_mutex_t));
	info->meals = malloc(sizeof(pthread_mutex_t));
	return (info);
}


int	main(int ac, char **av)
{
	t_philo	*philos;
	t_info	*info;
	int		istrue;

	philos = NULL;
	istrue = check_args(ac, av);
	if (istrue == 0)
		return (1);
	info = parse_args(ac, av);
	if (info == NULL)
		return (1);
	philos = create_philos(info);
	if (philos == NULL)
		return (write(2, "malloc failed\n", 15), free(info), 1);
	if (ac == 5)
		ft_start(philos, info->numofphilo);
	else if (ac == 6)
		ft_start_numofmeals(philos, info->numofphilo);
	ft_free(philos);
	return (0);
}
