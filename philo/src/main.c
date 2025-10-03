#include "philo.h"

int	exit_fail(char *flag)
{
	ft_putstr_fd("Error\n", 2);
	if (!flag)
		return (EXIT_FAILURE);
	else if (ft_strcmp(flag, "argc") == 0)
		ft_putstr_fd("Bad arguments\n", 2);
	else
	{
		ft_putstr_fd(flag, 2);
		ft_putstr_fd("\n", 2);
	}
	return (EXIT_FAILURE);
}

static void	free_table(t_table *table)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->n_philos)
			pthread_mutex_destroy(&table->forks[i++]);
		free(table->forks);
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->state_lock);
	if (table->philos)
		free(table->philos);
}

static int	args_parser(t_table *table, int argc, char **argv)
{
	int			i;
	t_timeval	tv;

	table->n_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	table->finished = 0;
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->state_lock, NULL);
	table->forks = malloc(sizeof(*table->forks) * (table->n_philos));
	if (!table->forks)
		return (exit_fail("malloc"));
	i = 0;
	while (i < table->n_philos)
		pthread_mutex_init(&table->forks[i++], NULL);
	gettimeofday(&tv, NULL);
	table->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (EXIT_SUCCESS);
}

static int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(*table->philos) * (table->n_philos));
	if (!table->philos)
		return (exit_fail("malloc"));
	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals = 0;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].table = table;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->n_philos];
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (exit_fail("argc"));
	memset(&table, 0, sizeof(table));
	if (args_parser(&table, argc, argv) == EXIT_FAILURE)
		return (free_table(&table), EXIT_FAILURE);
	if (init_philos(&table) == EXIT_FAILURE)
		return (free_table(&table), EXIT_FAILURE);
	if (philosophers(&table) == EXIT_FAILURE)
		return (free_table(&table), EXIT_FAILURE);
	return (free_table(&table), EXIT_SUCCESS);
}