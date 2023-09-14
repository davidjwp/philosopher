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

// this checks wether or not the philosophers are dead or have eaten enough
// int	check_death(t_thread *th)
// {
// 	pthread_mutex_lock(th->death_lock);
// 	if ((getcurrenttime() - th->death_time) >= th->dt.time_td)
// 	{
// 		if (!*(th->death))
// 		{
// 			if ((getcurrenttime() - th->death_time) >= th->dt.time_td)
// 				write_status(th, "died");
// 			*(th->death) = 1;
// 		}
// 		return (pthread_mutex_unlock(th->death_lock), 0);
// 	}
// 	else if (th->dt.num_pme && th->pme == th->dt.num_pme)
// 		return (pthread_mutex_unlock(th->death_lock), th->exit = 1, 0);
// 	else if (*(th->death))
// 		return (pthread_mutex_unlock(th->death_lock), 0);
// 	return (pthread_mutex_unlock(th->death_lock), 1);
// }

int	other_death(t_thread *th)
{
	pthread_mutex_lock(th->death_lock);
	// printf ("\nphilo %d is checking death state of %d and exit state of %d\n", th->nump, *th->death, th->exit);
	if (*th->death || th->exit)
		return (pthread_mutex_unlock(th->death_lock), 0);
	pthread_mutex_unlock(th->death_lock);
	return (1);
}


int	ft_sleep(t_thread *th, int time_to_sleep)
{
	time_to_sleep *= 10;
	while (time_to_sleep--)
	{
		if (!other_death(th))
			return (0);
		usleep(10);
	}
	return (1);
}

// void	myusleep(int time_to_sleep)
// {
// 	while (time_to_sleep--)
// 		usleep(1);
// }

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
		pthread_mutex_lock(th->death_lock);
		th->pme++;
		pthread_mutex_unlock(th->death_lock);
	}
	else
	{
		pthread_mutex_unlock(th->l_fork);
 		pthread_mutex_unlock(th->r_fork);
		pthread_mutex_lock(th->death_lock);
		th->pme++;
		pthread_mutex_unlock(th->death_lock);
	}
}


int	eating(t_thread *th)
{
	if (th->r_fork == NULL)
	{
		if (!th->fotak++)
			write_status(th, "has taken a fork");
		if (!other_death(th))
			return (0);		
		return (1);
	}
	picking_forks(th);
	if (!write_status(th, "is eating"))
		return (dropping_forks(th), 0);
	pthread_mutex_lock(th->death_lock);
	th->eating = 1;
	usleep(th->dt.time_te * 1000);
	th->death_time = getcurrenttime();
	th->eating = 0;
	pthread_mutex_unlock(th->death_lock);
	dropping_forks(th);
	if (th->dt.num_pme && th->pme == th->dt.num_pme)
		return (th->fotak--, 0);
	return (th->fotak--, sleep_think(th));
}


// int	eating(t_thread *th)
// {
// 	if (!check_death(th))
// 		return (0);
// 	if (th->r_fork == NULL)
// 	{
// 		if (!th->fotak++)
// 			write_status(th, "has taken a fork");
// 		return (1);
// 	}
// 	picking_forks(th);
// 	write_status(th, "is eating");
// 	usleep(th->dt.time_te * 1000);
// 	th->death_time = getcurrenttime();
// 	dropping_forks(th);
// 	if (!check_death(th))
// 		return (0);
// 	return (th->fotak--, sleep_think(th));
// }


int	sleep_think(t_thread *th)
{
	if (!write_status(th, "is sleeping"))
		return (0);
	if (!ft_sleep(th, th->dt.time_ts))
		return (0);
	write_status(th, "is thinking");
	return (1);
}

// int	sleep_think(t_thread *th)
// {
// 	if (!check_death(th))
// 		return (0);
// 	pthread_mutex_lock(th->death_lock);
// 	write_status(th, "is sleeping");
// 	pthread_mutex_unlock(th->death_lock);
// 	usleep(th->dt.time_ts * 1000);
// 	if (!check_death(th))
// 		return (0);
// 	write_status(th, "is thinking");
// 	if (!check_death(th))
// 		return (0);
// 	return (1);
// }
