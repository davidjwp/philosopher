/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:57:01 by djacobs           #+#    #+#             */
/*   Updated: 2023/08/27 18:57:03 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	getcurrenttime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}

//go through the routines make some eat and make some sleep and think 
int	check_death(t_thread *th)
{
	printf ("%lli\n", th->death_time - getcurrenttime());
	if ((getcurrenttime() - th->death_time) >= th->dt.time_td)
	{
		pthread_mutex_lock(&th->death_lock);
		th->death = 1;
		th->dead = 1;
		pthread_mutex_unlock(&th->death_lock);
		return (0);
	}
	return (1);
}

int	eating(t_thread *th)
{
	if (!pthread_mutex_lock(&th->l_fork))
	{
		th->fotak++;
		write_status(th, "has taken a fork");
	}
	if (th->r_fork == NULL)//HAHAHAHAAAAAAAAAAAAAAAAAAA FUCKING KILL ME
		return (0);
	if (!pthread_mutex_lock(th->r_fork))
	{
		write_status(th, "has taken a fork");
		write_status(th, "is eating");
		usleep(th->dt.time_te * 1000);
		th->death_time = getcurrenttime();
		check_death(th);
		pthread_mutex_unlock(&th->l_fork);
		pthread_mutex_unlock(th->r_fork);
		return(sleep_think(th), th->fotak--, 0);
	}
	return (0);
}

void	sleep_think(t_thread *th)
{
	write_status(th, "is sleeping");
	usleep(th->dt.time_ts * 1000);
	check_death(th);
	write_status(th, "is thinking");
}
