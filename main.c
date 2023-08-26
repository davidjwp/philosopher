#include "philosopher.h"
 
void	write_status(t_thread *th, char *status)
{
	long long int	mltime;

	mltime = getCurrentTime() - th->start_time;
	if (mltime < __LONG_MAX__)
		printf ("%lld Philo %i %s", mltime, th->numP + 1, status);
}

void	join_threads(t_thread *threads, t_data data)
{
	int	i;

	i = 0;
	while (i < data.numP)
	{
		if (pthread_join(threads[i].t_id, NULL) == 0)
			write_status(&threads[i], "died\n");
		i++;
	}
}

/*
release the forks that are taken and just repeat, write the messages withh the timestamps*/
void	*routine(void *data)
{
	t_thread	*th;

	th = (t_thread *)data;
	th->start_time = getCurrentTime();
	th->death_time = th->start_time;
	if (th->dt.numP == 3 && th->numP == 3)
		write_status(th, "is thinking\n");
	if (th->numP % 2 == 0)
		sleep_think(th);
	while (!th->dead)
	{
		eating(th);
		if (th->dt.numPME)
			if (th->dt.numPME == th->PME++)
				break;
		if (!th->dead)
			sleep_think(th);
	}
	if (th->dead)
		write_status(th, "died\n");
	return ((void *)0);
}

int main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_thread	*threads;
	t_data	data;
	int	i;

	i = 0;
	if (!check_argv(argc, argv, &data))
		return(write (1,"Error\n", 6), 0);
	forks = malloc(sizeof(pthread_mutex_t) * data.numP);
	threads = malloc(sizeof(t_thread) * data.numP);
	if (!mutex_init(data, threads, forks))
		return (free(threads), 0);
	while (i < data.numP)
	{
		pthread_create(&threads[i].t_id , NULL, routine, &threads[i]);
		i++;
	}
	join_threads(threads, data);
	free(forks);
	free(threads);
	return (0);
}

/*
make sure to release the mutex and threads when you are done like this pthread_mutex_destroy(&forks[i]) and free them
like this free(forks); 
and pthread_join(`.dblIDs[i], NULL)*/
/*
pthread_t	*thread;
const pthead_attr_t	*attr;
void	*(*start_routine)(void *);
void	*arg;

pthread_create(thread, attr, &start_routine, arg);
argv[1] 
- numbers_of_philosophers					numP
argv[2] 
- time_to_die								timeTD
argv[3] 
- time_to_eat								timeTE
argv[4] 
time_to_sleep								timeTS
argv[5]
number_of_times_each_philosopher_must_eat	numPME this defines whether the end of the simulation is dictated by the death 
of the philosophers or by when they reach this amount of time
*/
// philosopher num 1 > philosopher num 2 > philosopher num 3 order of philosophers 

/*
	create and allocate structures representing the threads containing the thread id
	left and right forks(mutex) 
*/