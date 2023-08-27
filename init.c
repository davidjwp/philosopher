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

int	mutex_init(t_data data, t_thread *threads, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (forks == NULL)
		return (perror("Error mutex init"), 0);
	while (i < data.nump)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < data.nump)
	{
		threads[i].nump = i;
		threads[i].dead = 0;
		threads[i].pme = 0;
		threads[i].dt = data;
		threads[i].l_fork = forks[i];
		if (i == (data.nump - 1))
			threads[i].r_fork = forks[0];
		else
			threads[i].r_fork = forks[i + 1];
		i++;
	}
	return (1);
}
