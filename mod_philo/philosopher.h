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
	int				fotak;
	int				nump;
	int				*death;
	int				exit;
	long long int	start_time;
	long long int	death_time;
	int				pme;
	int				eating;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	*death_lock;
	pthread_t		t_id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			dt;
}				t_thread;

//new
void	monitor(t_data dt, t_thread *th, int i, int pme);
int		other_death(t_thread *th);
void	write_death(t_thread *th, char *death);


//parse
int			check_argv(int argc, char **argv, t_data *d);

//init
int			init(t_data q, pthread_mutex_t *f, pthread_mutex_t d, t_thread *t);
int			mutex_init(t_data data, t_thread *th, pthread_mutex_t *f);

//utils
int		write_status(t_thread *th, char *status);
int			ft_strlen(char *s);
void		clean_forks(t_thread *threads, int i);
void		destroy_forks(pthread_mutex_t *mforks, pthread_mutex_t dl, int num);
void		err_msg(char *msg);

//thread function
int			sleep_think(t_thread *th);
int			eating(t_thread *th);
int			check_death(t_thread *th);
long long	getcurrenttime(void);
void		join_threads(t_thread *threads, t_data data);
void		*routine(void *arg);

#endif