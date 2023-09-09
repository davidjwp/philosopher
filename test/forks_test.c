
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

# include <unistd.h>
# include <sys/time.h>


#define	NUM_THREADS 4

int	sharedData = 0;

typedef struct	_thread_struc{
	pthread_t	t_id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int			t_num;
}				t_thread;

void	*accessing(t_thread *th)
{
	pthread_mutex_lock(th->l_fork);
	printf("Thread %d has picked up the left fork\n", th->t_num);
	pthread_mutex_lock(th->r_fork);
	printf("Thread %d has picked up the right fork\n", th->t_num);
	sharedData++;
	printf("Thread %d is accessing the shared data\n", th->t_num);
	usleep(1000);
	printf("Thread %d is dropping both forks\n", th->t_num);
	pthread_mutex_unlock(th->l_fork);
	pthread_mutex_unlock(th->r_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_thread	*th = (t_thread *)arg;
	return (accessing(th));
}

int main(void)
{
	pthread_mutex_t	*forks;
	t_thread		*th;


	forks = malloc(sizeof(pthread_mutex_t) * NUM_THREADS);
	th = malloc(sizeof(t_thread) * NUM_THREADS);
	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
		th[i].l_fork = &forks[i];
		if (i == NUM_THREADS - 1)
			th[i].r_fork = &forks[0];
		else
			th[i].r_fork = &forks[i + 1];
		th[i].t_num = i;
		pthread_create(&th[i].t_id, NULL, routine, &th[i]);
	}

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(th[i].t_id, NULL);

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_mutex_destroy(&forks[i]);
	
	free(th);
	free(forks);
}
