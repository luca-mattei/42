#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				finished;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	data_lock;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		last_meal;
	int			left_fork;
	int			right_fork;
	t_data		*data;
	pthread_t	thread;
}	t_philo;

/* Main functions */
int		parse_args(int ac, char **av, t_data *data);
int		init_data(t_data *data);
int		init_philos(t_philo **philos, t_data *data);
void	start_simulation(t_philo *philos, t_data *data);
void	cleanup(t_philo *philos, t_data *data);

/* Utils functions */
long	get_time(void);
void	ft_usleep(long time_ms);
void	print_status(t_philo *philo, char *status);
int		ft_atoi(const char *str);

/* Routine functions */
void	*philo_routine(void *arg);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	philo_eat(t_philo *philo);

/* Monitor functions */
void	*monitor_routine(void *arg);
int		check_death(t_philo *philos, t_data *data);
int		check_meals_complete(t_philo *philos, t_data *data);
int		is_finished(t_data *data);

#endif