#include "philosopher.h"

int	mutex_init(t_data data, t_thread *threads, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (forks == NULL)
		return (perror("Error mutex init"), 0);
	while (i < data.numP)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < data.numP)
	{
		threads[i].numP = i;
		threads[i].dead = 0;
		threads[i].PME = 0;
		threads[i].dt = data;
		threads[i].l_fork = forks[i];
		if (i == (data.numP - 1))
			threads[i].r_fork = forks[0];
		else
			threads[i].r_fork = forks[i + 1];
		i++;
	}
	return (1);
}