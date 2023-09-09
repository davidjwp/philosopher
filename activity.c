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

//this checks wether or not the philosophers are dead
int	check_death(t_thread *th)
{
	pthread_mutex_lock(th->death_lock);
	if ((getcurrenttime() - th->death_time) >= th->dt.time_td)
	{
		if (!*(th->death))
		{
			if ((getcurrenttime() - th->death_time) >= th->dt.time_td)
				write_status(th, "died");
			*(th->death) = 1;
		}
		return (pthread_mutex_unlock(th->death_lock), 0);
	}
	else if (th->dt.num_pme && th->pme == th->dt.num_pme)
		return (pthread_mutex_unlock(th->death_lock), th->exit = 1, 0);
	return (pthread_mutex_unlock(th->death_lock), 1);
}

int	eating(t_thread *th)
{
	if (!pthread_mutex_lock(th->l_fork) && !th->fotak)
	{
		th->fotak++;
		write_status(th, "has taken a fork");
	}
	if (th->r_fork == NULL)
		return (pthread_mutex_unlock(th->l_fork), 0);
	if (!pthread_mutex_lock(th->r_fork) && th->fotak)
	{
		if (!check_death(th))
			return (pthread_mutex_unlock(th->l_fork), \
			pthread_mutex_unlock(th->r_fork), 0);
		write_status(th, "has taken a fork");
		write_status(th, "is eating");
		usleep(th->dt.time_te * 1000);
		th->death_time = getcurrenttime();
		pthread_mutex_unlock(th->r_fork);
		pthread_mutex_unlock(th->l_fork);
		th->pme++;
		if (!check_death(th))
			return (0);
		return(sleep_think(th), th->fotak--, 0);
	}
	return (0);
}

int	sleep_think(t_thread *th)
{
	if (!check_death(th))
		return (0);
	write_status(th, "is sleeping");
	usleep(th->dt.time_ts * 1000);
	if (!check_death(th))
		return (0);
	write_status(th, "is thinking");
	return (1);
}
