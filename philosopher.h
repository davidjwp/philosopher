/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:06:21 by djacobs           #+#    #+#             */
/*   Updated: 2023/08/27 19:06:22 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct _global_data{
	int	nump;
	int	time_td;
	int	time_te;
	int	time_ts;
	int	num_pme;
}				t_data;

typedef struct _thread_struct{
	int				nump;
	int				dead;
	int				death;
	long long int	start_time;
	long long int	death_time;
	int				pme;
	pthread_t		t_id;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	t_data			dt;
}				t_thread;

int			mutex_init(t_data data, t_thread *threads, pthread_mutex_t *forks);
int			check_argv(int argc, char **argv, t_data *d);
void		write_status(t_thread *th, char *status);
void		sleep_think(t_thread *th);
void		tsleep(t_thread *th);
void		eating(t_thread *th);
int			check_death(t_thread *th);
long long	getcurrenttime(void);
int			ft_strlen(char *s);

#endif