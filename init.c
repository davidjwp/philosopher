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

/*
* here i initialize all the data and forks with shared data and mutexes 
* being in main_init
*/
int	mutex_init(t_data data, t_thread *threads, pthread_mutex_t *forks)
{
	int				i;

	i = 0;
	while (i < data.nump)
		if (pthread_mutex_init(&forks[i++], NULL) != 0)
			return (err_msg("mutex_init forks error"), clean_mutex(forks, i--), 0);
	i = 0;
	while (i < data.nump)
	{
		threads[i].exit = 0;
		threads[i].fotak = 0;
		threads[i].nump = i + 1;
		threads[i].pme = 0;
		threads[i].dt = data;
		threads[i].r_fork = NULL;
		threads[i].l_fork = &forks[i];
		if (i == (data.nump - 1) && data.nump > 1)
			threads[i].r_fork = &forks[0];
		else if (data.nump > 1)
			threads[i].r_fork = &forks[i + 1];
		i++;
	}
	return (1);
}

/*
* all the shared data starts in this scope or the previous one
*
* the forks and threads are allocated and initialized, then the threads are
* created, then joined and threads and forks freed
*/
int	main_init(t_data dt, pthread_mutex_t *forks, pthread_mutex_t dl)
{
	t_thread		*threads;
	int				death;
	int				i;

	i = 0;
	death = 0;
	forks = malloc(sizeof(pthread_mutex_t) * dt.nump);
	if (forks == NULL)
		return (err_msg("forks malloc fail"), 0);
	threads = malloc(sizeof(t_thread) * dt.nump);
	if (threads == NULL)
		return (err_msg("threads malloc fail"), free(forks), 1);
	if (!mutex_init(dt, threads, forks))
		return (0);
	pthread_mutex_init(&dl, NULL);
	while (i < dt.nump)
	{
		threads[i].death = &death;
		threads[i].death_lock = &dl;
		pthread_create(&threads[i].t_id, NULL, routine, (void *)&threads[i]);
		i++;
	}
	join_threads(threads, dt);
	return (destroy_forks(forks, dl, dt.nump), free(threads), free(forks), 2);
}
