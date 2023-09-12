/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:01:31 by djacobs           #+#    #+#             */
/*   Updated: 2023/08/27 19:01:32 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
* this function is only just in case of failure to initialize the forks mutex
* it'll destroy all the previous mutexes that were previously initialized
*/
void	clean_mutex(pthread_mutex_t *mutex, int num)
{
	int	i;

	i = 0;
	while (i < num)
		pthread_mutex_destroy(&mutex[i++]);
}

void	clean_forks(t_thread *threads, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (threads[i].l_fork != NULL)
			free(threads[i].l_fork);
		else
			break ;
		i++;
	}
	i = 0;
	while (i < num)
	{
		if (threads[i].r_fork != NULL)
			free(threads[i].r_fork);
		else
			break ;
		i++;
	}
}

int	al_forks(t_data data, t_thread *threads)
{
	int	i;

	i = 0;
	while (i < data.nump)
	{
		threads[i].l_fork = malloc(sizeof(pthread_mutex_t));
		// if (threads[i].l_fork == NULL)
		// {
		// 	err_msg("l_fork threads malloc fail");
		// 	return (clean_forks(threads, i), 0);
		// }
		threads[i].r_fork = malloc(sizeof(pthread_mutex_t));
		// if (threads[i].r_fork == NULL)
		// {
		// 	err_msg("r_fork threads malloc fail");
		// 	return (clean_forks(threads, i), 0);
		// }
		i++;
	}
	return (1);
}

/*
* here i initialize all the data and forks with shared data and mutexes 
* being in main_init
*/
int	mutex_init(t_data data, t_thread *threads, pthread_mutex_t *forks)
{
	int				i;

	i = 0;
	while (i < data.nump)
	{
		threads[i].exit = 0;
		threads[i].fotak = 0;
		threads[i].nump = i + 1;
		threads[i].pme = 0;
		threads[i].dt = data;
		threads[i].r_fork = NULL;
		pthread_mutex_init(&forks[i++], NULL);
	}
	i = 0;
	// printf ("address %p for l_fork and %p for forks given\n", threads[i].l_fork, &forks[i]);
	threads[0].l_fork = &forks[0];
	threads[0].r_fork = &forks[data.nump - 1];
	while (i++ < data.nump - 1)
	{
		// printf ("address %p for l_fork and %p for forks given\n", threads[i].l_fork, &forks[i]);
		threads[i].l_fork = &forks[i];
		if (data.nump > 1)
			threads[i].r_fork = &forks[i - 1];
	}
	return (1);
}

/*
* all the shared data starts in this scope or the previous one
*
* the forks and threads are allocated and initialized, then the threads are
* created, then joined and threads and forks freed
*/
int	init(t_data dt, pthread_mutex_t *f, pthread_mutex_t dl, t_thread *th)
{
	pthread_mutex_t	print_lock;
	int				death;
	int				i;

	i = 0;
	death = 0;
	// if (!al_forks(dt, th))
	// 	return (free(th), free(f), 0);
	// printf ("HERE\n");
	pthread_mutex_init(&print_lock, NULL);
	if (!mutex_init(dt, th, f))
		return (0);
	pthread_mutex_init(&dl, NULL);
	while (i < dt.nump)
	{
		th[i].print_lock = &print_lock;
		th[i].death = &death;
		th[i].death_lock = &dl;
		pthread_create(&th[i].t_id, NULL, routine, (void *)&th[i]);
		usleep(10);
		i++;
	}
	join_threads(th, dt);
	// clean_forks(th, dt.nump - 1);
	return (destroy_forks(f, dl, dt.nump), free(th), free(f), 2);
}
