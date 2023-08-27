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

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*itoa(long long n)
{
	char	*str;
	int		number;
	int		i;

	i = 0;
	number = n;
	while (number / 10)
	{
		number /= 10;
		i++;
	}
	str = malloc((i + 2) * sizeof(char));
	str[i + 1] = 0;
	while (i)
	{
		str[i--] = "0123456789"[n % 10];
		n = n / 10;
	}
	str[i] = "0123456789"[n % 10];
	return (str);
}

void	kill_all_philo(t_thread	*th)
{
	
}

void	destroy_forks(pthread_mutex_t *forks, pthread_mutex_t *d_lock, int num)
{
	int	i;

	i = 0;
	while (i < num)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(d_lock);
}