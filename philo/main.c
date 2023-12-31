/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:04:11 by djacobs           #+#    #+#             */
/*   Updated: 2023/08/27 19:04:12 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	destroy_forks(pthread_mutex_t *frks, pthread_mutex_t deathlocks, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&frks[i++]);
	pthread_mutex_destroy(&deathlocks);
}

void	join_threads(t_thread *threads, t_data data)
{
	int	i;

	i = 0;
	while (i < data.nump)
		pthread_join(threads[i++].t_id, NULL);
}

/*
* the routine by which every thread goes through
*/
void	*routine(void *arg)
{
	t_thread	*th;

	th = (t_thread *)arg;
	if (th->r_fork == NULL)
	{
		write_status(th, "has taken a fork");
		return (ft_sleep(th, th->dt.time_td + 1), NULL);
	}
	if ((th->dt.nump % 2 != 0 && th->nump == th->dt.nump) && th->nump != 1)
		write_status(th, "is thinking");
	if (th->nump % 2 == 0)
		if (!sleep_think(th))
			return (NULL);
	while (42)
	{
		if (!eating(th))
			return (NULL);
		if (!other_death(th))
			return (NULL);
	}
	return (NULL);
}

/*
* the monitoring function serves to continualy check for the time to death
* in every thread and when all threads have eaten enough if the argument is 
* added, when one of each is true, the simulation stops.
*/
int	monitor(t_data data, t_thread *th, int i, int pme)
{
	while (i < data.nump)
	{
		pthread_mutex_lock(th[i].d_lock);
		if (((getcurrenttime() - th[i].death_time) >= data.time_td) && \
		(!th[i].exit && !*th[i].death))
		{
			write_death(&th[i], "died");
			*th[i].death = 1;
			return (pthread_mutex_unlock(th[i].d_lock), 0);
		}
		else if (data.num_pme && th[i].pme == data.num_pme && !th[i].exit)
		{
			pme++;
			th[i].exit = 1;
		}
		if (pme == data.nump)
			return (*th[i].death = 1, pthread_mutex_unlock(th[i].d_lock), 1);
		pthread_mutex_unlock(th[i].d_lock);
		i++;
		if (i == data.nump)
			i = 0;
		slow_monitor(data);
	}
	return (2);
}

/*
*	the main is mostly there for higher scope forks and parsing
*/
int	main(int argc, char **argv)
{
	pthread_mutex_t	d_lock;
	pthread_mutex_t	*forks;
	t_thread		*threads;
	t_data			data;

	forks = NULL;
	if (!check_argv(argc, argv, &data))
		return (err_msg("bad arguments"), 0);
	forks = malloc(sizeof(pthread_mutex_t) * data.nump);
	if (forks == NULL)
		return (err_msg("forks malloc fail"), 0);
	threads = malloc(sizeof(t_thread) * data.nump);
	if (threads == NULL)
		return (err_msg("threads malloc fail"), free(forks), 1);
	if (!init(data, forks, d_lock, threads))
		return (0);
	return (1);
}
