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
	second i initialize the same mutex for every thread
	this mutex will lock when checking death status.
	if death is found then they are all dead but via
	a shared integer but only the one who died will 
	write that it is dead.
*/
// void	death_init(t_thread *threads, t_data data)
// {
// 	pthread_mutex_t	death_lock;
// 	int	i;

// 	i = 0;
// 	pthread_mutex_init(&death_lock, NULL);
// 	while (i < data.nump)
// 	{
// 		threads[i].death_lock = malloc(sizeof(pthread_mutex_t));
// 		threads[i].death_lock = &death_lock;
// 		i++;
// 	}
// }

//the problem of the mutexes staying open despite not being initialized might be due to this
int	mutex_init(t_data data, t_thread *threads, pthread_mutex_t *forks)
{
	int				death;
	int				i;

	i = 0;
	death = 0;
	while (i < data.nump)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < data.nump)
	{
		threads[i].fotak = 0;
		threads[i].nump = i + 1;
		threads[i].dead = 0;
		threads[i].death = &death;
		threads[i].pme = 0;
		threads[i].dt = data;
		threads[i].r_fork = NULL;
		threads[i].l_fork = forks[i];
		if (i == (data.nump - 1) && data.nump > 1)
			threads[i].r_fork = &forks[0];
		else if (data.nump > 1)
			threads[i].r_fork = &forks[i + 1];
		i++;
	}
	return (/*smutex_init(threads, data),*/ 1);
}
