#include "philo.h"

void	thinking_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%ld %d is thinking\n", get_timestamp(philo->table), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	pickup_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
}

void	eating_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%ld %d is eating\n", get_timestamp(philo->table), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	philo->last_meal = get_timestamp(philo->table);
	philo->meals++;
	usleep(philo->table->time_to_eat * 1000);
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	sleeping_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%ld %d is sleeping\n", get_timestamp(philo->table), philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	usleep(philo->table->time_to_sleep * 1000);
}