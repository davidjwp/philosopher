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

int	mutex_death_init(t_thread *threads, t_data data)
{
	pthread_mutex_t	death_lock;
	int	i;

	i = 0;
	while (i < data.nump)
		threads[i].death_lock;
}

int	mutex_init(t_data data, t_thread *threads, pthread_mutex_t *forks)
{
	int	i;
	int	death;

	i = 0;
	death = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.nump);
	if (forks == NULL)
		return (perror("Error mutex init\n"), 0);
	while (i < data.nump)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < data.nump)
	{
		threads[i].nump = i;
		threads[i].dead = 0;
		threads[i].death = death;
		threads[i].pme = 0;
		threads[i].dt = data;
		threads[i].l_fork = forks[i];
		if (i == (data.nump - 1))
			threads[i].r_fork = forks[0];
		else
			threads[i].r_fork = forks[i + 1];
		i++;
	}
	return (mutex_death_init(threads, data), 1);
}
