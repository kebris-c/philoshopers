#include "philo.h"

static void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->table->finished)
	{
		thinking_action(philo);
		pickup_forks(philo);
		eating_action(philo);
		drop_forks(philo);
		sleeping_action(philo);
	}
	return (NULL);
}

static t_bool	dead_checker(t_table *table, int i)
{
	t_timeval	tv;
	long		curr_time;

	gettimeofday(&tv, NULL);
	curr_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (curr_time - table->philos[i].last_meal > table->time_to_die)
	{
		pthread_mutex_lock(&table->print_lock);
		printf("%ld %d died\n", curr_time - table->start_time, table->philos[i].id);
		pthread_mutex_unlock(&table->print_lock);
		table->finished = 1;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	food_is_gone(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
		if (table->philos[i++].meals < table->must_eat)
			return (FALSE);
	pthread_mutex_lock(&table->print_lock);
	printf("%ld Simulation ended: all philosophers ate %d times\n", curr_time - table->start_time, table->must_eat);
	pthread_mutex_unlock(&table->print_lock);
	table->finished = 1;
	return (TRUE);
}

static void	*monitor_routine(void *arg)
{
	t_philo		*table;
	int			i;

	table = (t_table *)arg;
	while (!table->finished)
	{
		i = 0;
		while (i < table->n_philos)
			if (dead_checker(table, i++))
				return (NULL);
		if (table->must_eat != -1 && food_is_gone(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	philosophers(t_table *t)
{
	int			i;
	t_thread	monitor;

	i = 0;
	while (i < t->n_philos)
	{
		if (pthread_create(&t->philos[i].thread, NULL, &philos_routine, &t->philos[i]) != 0)
			return (exit_fail("pthread_create philo"));
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitor_routine, t) != 0)
		return (exit_fail("pthread_create monitor"));
	i = 0;
	while (i < t->n_philos)
	{
		pthread_join(t->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (EXIT_SUCCESS);
}