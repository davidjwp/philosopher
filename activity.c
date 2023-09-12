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

//this checks wether or not the philosophers are dead or have eaten enough
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
	else if (*(th->death))
		return (pthread_mutex_unlock(th->death_lock), 0);
	return (pthread_mutex_unlock(th->death_lock), 1);
}

void	picking_forks(t_thread *th)
{
	pthread_mutex_lock(th->l_fork);
	write_status(th, "has taken a fork");
	pthread_mutex_lock(th->r_fork);
	write_status(th, "has taken a fork");
}

void	dropping_forks(t_thread *th)
{
	pthread_mutex_unlock(th->r_fork);
	pthread_mutex_unlock(th->l_fork);
	th->pme++;
}

int	eating(t_thread *th)
{
	if (th->r_fork == NULL)
	{
		if (!th->fotak++)
			write_status(th, "has taken a fork");
		return (1);
	}
	picking_forks(th);
	write_status(th, "is eating");
	usleep(th->dt.time_te * 1000);
	th->death_time = getcurrenttime();
	dropping_forks(th);
	if (!check_death(th))
		return (0);
	return (sleep_think(th), th->fotak--, 1);
}

int	sleep_think(t_thread *th)
{
	if (!check_death(th))
		return (0);
	pthread_mutex_lock(th->death_lock);
	write_status(th, "is sleeping");
	pthread_mutex_unlock(th->death_lock);
	usleep(th->dt.time_ts * 1000);
	if (!check_death(th))
		return (0);
	write_status(th, "is thinking");
	if (!check_death(th))
		return (0);
	return (1);
}
