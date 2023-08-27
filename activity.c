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

//might be useless since i don't use it
// void	tsleep(t_thread *th)
// {
// 	write_status(th, "is sleeping\n");
// 	usleep(th->dt.time_ts * 1000);
// }

//go through the routines make some eat and make some sleep and think 
int	check_death(t_thread *th)
{
	if ((getcurrenttime() - th->death_time) < th->dt.time_td)
		return (0);
	return (1);
}

void	eating(t_thread *th)
{
	pthread_mutex_lock(&th->l_fork);
	pthread_mutex_lock(&th->r_fork);
	usleep(th->dt.time_te * 1000);
	write_status(th, "is eating\n");
	th->death_time = getcurrenttime();
	if ((th->death_time - getcurrenttime()) >= th->dt.time_td)
		th->dead = 1;
	pthread_mutex_unlock(&th->l_fork);
	pthread_mutex_unlock(&th->r_fork);
}

void	sleep_think(t_thread *th)
{
	usleep(th->dt.time_ts * 1000);
	write_status(th, "is sleeping\n");
	write_status(th, "is thinking\n");
}
