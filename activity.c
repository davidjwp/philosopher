#include "philosopher.h"

long long getCurrentTime() {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}

void	Tsleep(t_thread *th)
{
	write_status(th, "is sleeping\n");
	usleep(th->dt.timeTS * 1000);
}

//go through the routines make some eat and make some sleep and think 
int	check_death(t_thread *th)
{
	if ((getCurrentTime() - th->death_time) < th->dt.timeTD)
		return (0);
	return (1);
}

void	eating(t_thread *th)
{
	pthread_mutex_lock(&th->l_fork);
	pthread_mutex_lock(&th->r_fork);
	usleep(th->dt.timeTE * 1000);
	write_status(th, "is eating\n");
	th->death_time = getCurrentTime();
	if ((th->death_time - getCurrentTime()) >= th->dt.timeTD)
		th->dead = 1;	
	pthread_mutex_unlock(&th->l_fork);
	pthread_mutex_unlock(&th->r_fork);
}

void	sleep_think(t_thread *th)
{
	usleep(th->dt.timeTS * 1000);
	write_status(th, "is sleeping\n");
	write_status(th, "is thinking\n");
}
