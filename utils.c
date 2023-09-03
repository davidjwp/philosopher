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
	write(1, msg,ft_strlen(msg));
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

void	write_status(t_thread *th, char *status)
{
	long long int	mltime;

	mltime = getcurrenttime() - th->start_time;
	if (mltime < __LONG_MAX__)
		printf ("%lld Philo %i %s\n", mltime, th->nump, status);
}

// char	*itoa(long long n)
// {
// 	char	*str;
// 	int		number;
// 	int		i;

// 	i = 0;
// 	number = n;
// 	while (number / 10)
// 	{
// 		number /= 10;
// 		i++;
// 	}
// 	str = malloc((i + 2) * sizeof(char));
// 	str[i + 1] = 0;
// 	while (i)
// 	{
// 		str[i--] = "0123456789"[n % 10];
// 		n = n / 10;
// 	}
// 	str[i] = "0123456789"[n % 10];
// 	return (str);
// }
