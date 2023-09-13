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
	th->start_time = getcurrenttime();
	th->death_time = th->start_time;
	if (th->nump % 2 == 0 || th->dt.nump == 1)
		if (!sleep_think(th))
			return (NULL);
	while (!th->exit)
	{
		if (!eating(th))
			return (NULL);
		if (th->dt.num_pme && !*(th->death))
			if (th->pme == th->dt.num_pme)
				return (NULL);
		if (!check_death(th))
			return (NULL);
	}
	return (NULL);
}

void	monitor(t_data data, t_thread *th)
{
	int	i;

	i = 0;
	while (i < data.nump)
	{
		pthread_mutex_lock(th[i].death_lock);
		if (!*th[i].death)
		{
			if ((getcurrenttime() - th[i].death_time) >= data.time_td)
			{
				write_status(th, "died");
				*th[i].death = 1;
			}
		}
		else
		{
			pthread_mutex_unlock(th[i].death_lock);
			break ;
		}
		pthread_mutex_unlock(th[i].death_lock);
		i++;
		if (i == data.nump)
			i = 0;
	}
}


/*
*	the main is mostly there for higher scope forks and parsing
*/
int	main(int argc, char **argv)
{
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*forks;
	t_thread		*threads;
	t_data			data;

	forks = NULL;
	if (!check_argv(argc, argv, &data))`
		return (err_msg("bad arguments"), 0);
	forks = malloc(sizeof(pthread_mutex_t) * data.nump);
	if (forks == NULL)
		return (err_msg("forks malloc fail"), 0);
	threads = malloc(sizeof(t_thread) * data.nump);
	if (threads == NULL)
		return (err_msg("threads malloc fail"), free(forks), 1);
	if (!init(data, forks, death_lock, threads))
		return (0);
	return (1);
}


/*
	you should try and change the way that death is reported, if it doesn't work the original way is working anyways
	it's just that it might slow down the code a little bit, secure everything though and it should be fine 
*/