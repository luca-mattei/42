#include "philo.h"

int	parse_args(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
		return (printf("Error: Wrong number of arguments\n"), 1);
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -1;
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (ac == 6 && data->must_eat_count <= 0))
		return (printf("Error: Invalid arguments\n"), 1);
	return (0);
}

int	init_data(t_data *data)
{
	int	i;

	data->finished = 0;
	data->start_time = get_time();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->data_lock, NULL))
		return (1);
	return (0);
}

int	init_philos(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal = 0;
		(*philos)[i].left_fork = i;
		(*philos)[i].right_fork = (i + 1) % data->num_philos;
		(*philos)[i].data = data;
		i++;
	}
	return (0);
}

void	start_simulation(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return ;
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philos))
		return ;
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	memset(&data, 0, sizeof(t_data));
	if (parse_args(ac, av, &data))
		return (1);
	if (init_data(&data))
		return (cleanup(NULL, &data), 1);
	if (init_philos(&philos, &data))
		return (cleanup(philos, &data), 1);
	start_simulation(philos, &data);
	cleanup(philos, &data);
	return (0);
}