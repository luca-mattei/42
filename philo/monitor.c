#include "philo.h"

int	is_finished(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->data_lock);
	result = data->finished;
	pthread_mutex_unlock(&data->data_lock);
	return (result);
}

int	check_death(t_philo *philos, t_data *data)
{
	int		i;
	long	current_time;
	long	time_since_meal;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->data_lock);
		current_time = get_time() - data->start_time;
		time_since_meal = current_time - philos[i].last_meal;
		if (time_since_meal > data->time_to_die)
		{
			data->finished = 1;
			pthread_mutex_unlock(&data->data_lock);
			pthread_mutex_lock(&data->print_lock);
			printf("%ld %d died\n", current_time, philos[i].id);
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->data_lock);
		i++;
	}
	return (0);
}

int	check_meals_complete(t_philo *philos, t_data *data)
{
	int	i;
	int	all_ate_enough;

	if (data->must_eat_count == -1)
		return (0);
	all_ate_enough = 1;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->data_lock);
		if (philos[i].meals_eaten < data->must_eat_count)
			all_ate_enough = 0;
		pthread_mutex_unlock(&data->data_lock);
		if (!all_ate_enough)
			break ;
		i++;
	}
	if (all_ate_enough)
	{
		pthread_mutex_lock(&data->data_lock);
		data->finished = 1;
		pthread_mutex_unlock(&data->data_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (!is_finished(data))
	{
		if (check_death(philos, data) || check_meals_complete(philos, data))
			break ;
		usleep(1000);
	}
	return (NULL);
}