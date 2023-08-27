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

void	write_status(t_thread *th, char *status)
{
	long long int	mltime;

	mltime = getcurrenttime() - th->start_time;
	if (mltime < __LONG_MAX__)
		printf ("%lld Philo %i %s", mltime, th->nump + 1, status);
}

void	join_threads(t_thread *threads, t_data data)
{
	int	i;

	i = 0;
	while (i < data.nump)
	{
		if (pthread_join(threads[i].t_id, NULL) == 0 && threads[i].dead)
			write_status(&threads[i], "died\n");
		i++;
	}
}

void	*routine(void *data)
{
	t_thread	*th;

	th = (t_thread *)data;
	th->start_time = getcurrenttime();
	th->death_time = th->start_time;
	if (th->dt.nump == 3 && th->nump == 3)
		write_status(th, "is thinking\n");
	if (th->nump % 2 == 0)
		sleep_think(th);
	while (!th->death)//might need to change that
	{
		eating(th);
		if (th->dt.num_pme)
			if (th->dt.num_pme == th->pme++)
				break ;
		if (!th->dead)
			sleep_think(th);
	}
	if (th->dead)
		write_status(th, "died\n");
	return ((void *)0);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_thread		*threads;
	t_data			data;
	int				i;

	i = 0;
	if (!check_argv(argc, argv, &data))
		return (write (1, "Error\n", 6), 0);
	forks = malloc(sizeof(pthread_mutex_t) * data.nump);
	threads = malloc(sizeof(t_thread) * data.nump);
	if (!mutex_init(data, threads, forks))
		return (free(threads), 0);
	while (i < data.nump)
	{
		pthread_create(&threads[i].t_id, NULL, routine, &threads[i]);
		i++;
	}
	join_threads(threads, data);
	free(forks);
	free(threads);
	return (0);
}
