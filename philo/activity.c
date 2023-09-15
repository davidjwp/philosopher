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

int	ft_sleep(t_thread *th, int time_to_sleep)
{
	long long int	start_time;

	start_time = getcurrenttime();
	while ((getcurrenttime() - start_time) < time_to_sleep)
	{
		if (!other_death(th))
			return (0);
		usleep(time_to_sleep / 10);
	}
	return (1);
}

void	picking_forks(t_thread *th)
{
	if (th->nump % 2)
	{
		pthread_mutex_lock(th->l_fork);
		write_status(th, "has taken a fork");
		pthread_mutex_lock(th->r_fork);
		write_status(th, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(th->r_fork);
		write_status(th, "has taken a fork");
		pthread_mutex_lock(th->l_fork);
		write_status(th, "has taken a fork");
	}
}

void	dropping_forks(t_thread *th)
{
	if (th->nump % 2)
	{
		pthread_mutex_unlock(th->r_fork);
		pthread_mutex_unlock(th->l_fork);
		pthread_mutex_lock(th->d_lock);
		th->pme++;
		pthread_mutex_unlock(th->d_lock);
	}
	else
	{
		pthread_mutex_unlock(th->l_fork);
		pthread_mutex_unlock(th->r_fork);
		pthread_mutex_lock(th->d_lock);
		th->pme++;
		pthread_mutex_unlock(th->d_lock);
	}
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
	if (!ft_sleep(th, th->dt.time_te))
		return (dropping_forks(th), 0);
	pthread_mutex_lock(th->d_lock);
	th->death_time = getcurrenttime();
	pthread_mutex_unlock(th->d_lock);
	dropping_forks(th);
	return (th->fotak--, sleep_think(th));
}

int	sleep_think(t_thread *th)
{
	if (!write_status(th, "is sleeping"))
		return (0);
	if (!ft_sleep(th, th->dt.time_ts))
		return (0);
	if (th->dt.nump % 2 == 1 && th->dt.time_te > th->dt.time_ts)
	{
		write_status(th, "is thinking");
		if (!ft_sleep(th, th->dt.time_te))
			return (0);
	}
	else
		if (!write_status(th, "is thinking"))
			return (0);
	return (1);
}
