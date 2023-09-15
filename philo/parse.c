/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:05:06 by djacobs           #+#    #+#             */
/*   Updated: 2023/08/27 19:05:07 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(char *s)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (s[++i])
		num = (num * 10) + (s[i] - 48);
	return (num);
}

//check that the arguments are the proper numbers and not too small
int	check_num(int argc, char **argv, t_data *data)
{
	data->nump = ft_atoi(argv[1]);
	data->time_td = ft_atoi(argv[2]);
	data->time_te = ft_atoi(argv[3]);
	data->time_ts = ft_atoi(argv[4]);
	data->num_pme = 0;
	if (argc == 6)
		data->num_pme = ft_atoi(argv[5]);
	else
		data->num_pme = 0;
	if (data->nump < 1 || data->time_td < 1 || data->time_te < 1 || \
	data->time_ts < 1)
		return (0);
	return (1);
}

//checks that the arguments are only numbers
int	check_argv(int argc, char **argv, t_data *d)
{
	int	y;
	int	i;

	y = argc;
	if (argc < 5 || argc > 6)
		return (0);
	while (y--)
	{
		i = 0;
		while (argv[y][i] != 0 && y != 0)
		{
			if (!(argv[y][i] >= '0' && argv[y][i] <= '9'))
				return (0);
			i++;
		}
	}
	if (!check_num(argc, argv, d))
		return (0);
	return (1);
}
