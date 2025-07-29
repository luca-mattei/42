#include "philo.h"

void	cleanup(t_philo *philos, t_data *data)
{
	int	i;

	if (philos)
		free(philos);
	if (data && data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data)
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->data_lock);
	}
}