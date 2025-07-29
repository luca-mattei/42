#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	philo_eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->data_lock);
	philo->last_meal = get_time() - philo->data->start_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->data_lock);
	ft_usleep(philo->data->time_to_eat);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(30);
	while (!is_finished(philo->data))
	{
		print_status(philo, "is thinking");
		take_forks(philo);
		philo_eat(philo);
		drop_forks(philo);
		if (is_finished(philo->data))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}