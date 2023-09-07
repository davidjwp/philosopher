/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:04:11 by djacobs           #+#    #+#             */
/*   Updated: 2023/08/27 19:04:12 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	destroy_forks(pthread_mutex_t *forks, pthread_mutex_t death_locks, int num)
{
	int	i;

	i = 0;
	while (i < num)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(&death_locks);
}

void	join_threads(t_thread *threads, t_data data)
{
	int	i;

	i = 0;
	while (i < data.nump)
	{
		if (pthread_join(threads[i].t_id, NULL) == 0 && threads[i].dead \
		&& threads[i].death)
				write_status(&threads[i++], "died");
			i++;
	}
}

/*
	the routine by which every thread goes through
*/
void	*routine(void *arg)
{
	t_thread	*th;

	th = (t_thread *)arg;
	th->start_time = getcurrenttime();
	th->death_time = th->start_time;
	if (th->dt.nump == 3 && th->nump == 3)
		write_status(th, "is thinking");
	if (th->nump % 2 == 0)
		sleep_think(th);
	while (!*(th->death))
	{
		if (!*(th->death))
			eating(th);
		if (th->dt.num_pme && !*(th->death))
			if (th->dt.num_pme == th->pme++)
				return((void *)0);
		check_death(th);
	}
	return ((void *)0);
}	
int	main(int argc, char **argv)
{
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*forks;
	t_thread		*threads;
	t_data			data;
	int				i;

	i = 0;
	if (!check_argv(argc, argv, &data))
		return (err_msg("bad arguments"), 0);
	forks = malloc(sizeof(pthread_mutex_t) * data.nump);
	threads = malloc(sizeof(t_thread) * data.nump);
	if (threads == NULL)
		return (err_msg("threads malloc fail"), 0);
	mutex_init(data, threads, forks);
	pthread_mutex_init(&death_lock, NULL);
	while (i < data.nump)
	{
		threads[i].death_lock = &death_lock;
		pthread_create(&threads[i].t_id, NULL, routine, (void *)&threads[i]);
		i++;
	}
	join_threads(threads, data);
	destroy_forks(forks, death_lock, data.nump);
	return (free(threads), free(forks), 2);
}

//consider creating a condition to end the simulation if it's taking too long so that even without a condition you don't have to send an abort signal to stop the process 

/*
you should only worry about failure cases when the main code works we

if the number of times each philosopher must eat is not specified then they will eat until one of them dies

in which case the simulation is ended, if the number is given then none of them will die and the program will simply
end.

main - activities - init - utils

*/

/*the main fix needed is for the philosopher to only die if they starve

meaning that if they reach the number for the amount of eating the program should just stop

also if one of them dies the program should just stop after that but only the philosopher that
died is dead in another word only one philosopher dies if any of them do

i use a shared integer death that is turned on when one of them dies so they all know to stop,
then onlly the one who is dead is declared dead

also i don't know if when one of the pihlosopher reaches the number eaten they should all stop 
or they stop once each has reached that goal or if that even matters since it probably doesn't make a difference

also keep in mind that if a only one philosopher is present that also means that only fork is present
and since you need two forks to eat he won't be able to and die
*/
