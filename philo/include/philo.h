#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>

typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef struct s_philo	t_philo;

typedef struct	s_table
{
	int		n_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		must_eat;
	int		finished;
	t_mutex	print_lock;
	t_mutex	state_lock;
	long	start_time;
	t_mutex	*forks;
	t_philo	*philos;
}	t_table;

typedef struct	s_philo
{
	int			id;
	int			meals;
	long		last_meal;
	t_thread	thread;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_table		*table;
}	;

int		philosophers(t_table *table);
int		exit_fail(char *flag);
void	thinking_action(t_philo *philo);
void	pickup_forks(t_philo *philo);
void	eating_action(t_philo *philo);
void	drop_forks(t_philo *philo);
void	sleeping_action(t_philo *philo);
long	get_timestamp(t_table *table);

#endif