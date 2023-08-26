#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H


# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct	_global_data{
	int			numP;
	int			timeTD;
	int			timeTE;
	int			timeTS;
	int			numPME;
}				t_data;

typedef struct	_thread_struct{
	int				numP;
	int				dead;
	long long int	start_time;
	long long int	death_time;
	int				PME;
	pthread_t		t_id;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	t_data			dt;
}				t_thread;

int	mutex_init(t_data data, t_thread *threads, pthread_mutex_t *forks);
int check_argv(int argc, char **argv, t_data *d);
void	write_status(t_thread *th, char *status);
void	sleep_think(t_thread *th);
void	Tsleep(t_thread *th);
void	eating(t_thread *th);
int	check_death(t_thread *th);
long long getCurrentTime();
int	ft_strlen(char *s);


#endif


// number_of_philosopher - time_to_die - time_to_eat

// time_to_sleep number_of_times_each_philosopher_must_eat

// philosopher num 1 > philosopher num 2 > philosopher num 3 order of philosophers 