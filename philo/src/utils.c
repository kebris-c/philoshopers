#include "philo.h"

long	get_timestamp(t_table *table)
{
	t_timeval	tv;
	long		timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000 - table->start_time;
	return (timestamp);
}