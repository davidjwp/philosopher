/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:07:05 by djacobs           #+#    #+#             */
/*   Updated: 2023/08/27 19:07:06 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	err_msg(char *msg)
{
	write(1, "Error ", 6);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	write_death(t_thread *th, char *status)
{
	long long int	mltime;

	mltime = getcurrenttime() - th->start_time;
	pthread_mutex_lock(th->print_lock);
	if (mltime < __LONG_MAX__)
		printf ("%lld %i %s\n", mltime, th->nump, status);
	pthread_mutex_unlock(th->print_lock);
}

int	write_status(t_thread *th, char *status)
{
	long long int	mltime;

	if (!other_death(th))
		return (0);
	mltime = getcurrenttime() - th->start_time;
	pthread_mutex_lock(th->print_lock);
	if (mltime < __LONG_MAX__)
		printf ("%lld %i %s\n", mltime, th->nump, status);
	pthread_mutex_unlock(th->print_lock);
	return (1);
}

long long	getcurrenttime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}
