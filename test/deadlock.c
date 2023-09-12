// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>

// typedef	struct __thread_t{
// 	pthread_t		t_id;
// 	pthread_mutex_t	*lockA;
// 	pthread_mutex_t	*lockB;
// 	int				num;
// }				t_thread;

// void	*routineA(void *arg)
// {
// 	t_thread	*th = (t_thread *)arg;

// 	pthread_mutex_lock(th->lockA);
// 	pthread_mutex_lock(th->lockB);

// 	write (1, "threadA acquires all locks\n", 27);

// 	pthread_mutex_unlock(th->lockA);
// 	pthread_mutex_unlock(th->lockB);

// 	write (1,"threadA releases all locks\n", 27);
// }

// void	*routineB(void *arg)
// {
// 	t_thread	*th = (t_thread*)arg;

// 	pthread_mutex_lock(th->lockA);
// 	pthread_mutex_lock(th->lockB);

// 	write (1, "threadB acquires all locks\n", 27);

// 	pthread_mutex_unlock(th->lockA);
// 	pthread_mutex_unlock(th->lockB);

// 	write (1,"threadB releases all locks\n", 27);
// }


// int main(void)
// {
// 	t_thread	threadA;
// 	t_thread	threadB;

// 	pthread_mutex_t	lockA;
// 	pthread_mutex_t	lockB;

// 	pthread_mutex_init(&lockA, NULL);
// 	pthread_mutex_init(&lockB, NULL);

// 	threadA.lockA = &lockA;
// 	threadA.lockB = &lockB;

// 	threadB.lockA = &lockA;
// 	threadB.lockB = &lockB;

// 	pthread_create(&threadA.t_id, NULL, routineA, &threadA);
// 	pthread_create(&threadB.t_id, NULL, routineB, &threadB);

// 	pthread_join(threadA.t_id, NULL);
// 	pthread_join(threadB.t_id, NULL);

// 	pthread_mutex_destroy(&lockA);
// 	pthread_mutex_destroy(&lockB);

// 	return (0);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>

// typedef	struct __thread_t{
// 	pthread_t		t_id;
// 	pthread_mutex_t	*lockA;
// 	pthread_mutex_t	*lockB;
// 	int				num;
// }				t_thread;

// void	*routineA(void *arg)
// {
// 	t_thread	*th = (t_thread *)arg;

// 	pthread_mutex_lock(th->lockA);
// 	pthread_mutex_lock(th->lockB);

// 	write (1, "threadA acquires all locks\n", 27);

// 	pthread_mutex_unlock(th->lockA);
// 	pthread_mutex_unlock(th->lockB);

// 	write (1,"threadA releases all locks\n", 27);
// }

// void	*routineB(void *arg)
// {
// 	t_thread	*th = (t_thread*)arg;

// 	pthread_mutex_lock(th->lockA);
// 	pthread_mutex_lock(th->lockB);

// 	write (1, "threadB acquires all locks\n", 27);

// 	pthread_mutex_unlock(th->lockA);
// 	pthread_mutex_unlock(th->lockB);

// 	write (1,"threadB releases all locks\n", 27);
// }


// int main(void)
// {
// 	t_thread	threadA;
// 	t_thread	threadB;

// 	pthread_mutex_t	all_locks[2];

// 	for (int i = 0; i < 2; i++)
// 		pthread_mutex_init(&all_locks[i], NULL);

// 	threadA.lockA = &all_locks[0];
// 	threadA.lockB = &all_locks[1];

// 	threadB.lockA = &all_locks[0];
// 	threadB.lockB = &all_locks[1];

// 	pthread_create(&threadA.t_id, NULL, routineA, &threadA);
// 	pthread_create(&threadB.t_id, NULL, routineB, &threadB);

// 	pthread_join(threadA.t_id, NULL);
// 	pthread_join(threadB.t_id, NULL);

// 	for (int i = 0; i < 2; i++)
// 		pthread_mutex_destroy(&all_locks[i]);

// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define	NUM_THREADS	8

typedef	struct __thread_t{
	pthread_t		t_id;
	pthread_mutex_t	*lockA;
	pthread_mutex_t	*lockB;
	int				*death;
	pthread_mutex_t	*death_lock;
	int				num;
}				t_thread;

int		check_death(t_thread *th)
{
	pthread_mutex_lock(th->death_lock);
	if (th->num % 2 == 0)
	{
		if (!*th->death)
			*th->death = 1;
	}
	pthread_mutex_unlock(th->death_lock);
}

void	*routineA(void *arg)
{
	t_thread	*th = (t_thread *)arg;

	if (th->num % 2 == 0)
		usleep(1000);
	if (!check_death(th))
		return (NULL);
	pthread_mutex_lock(th->lockA);
	pthread_mutex_lock(th->lockB);

	printf("Thread %d has acquired all locks\n", th->num);

	pthread_mutex_unlock(th->lockA);
	pthread_mutex_unlock(th->lockB);

	printf("Thread %d has dropped all locks\n", th->num);	
}

int main(void)
{
	t_thread	*threads;

	int			death;

	death = 0;

	pthread_mutex_t	*all_locks;
	pthread_mutex_t	death_lock;

	threads = malloc(sizeof(t_thread) * NUM_THREADS);

	all_locks = malloc(sizeof(pthread_mutex_t) * NUM_THREADS);

	pthread_mutex_init(&death_lock, NULL);
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_mutex_init(&all_locks[i], NULL);
	
	threads[0].lockA = &all_locks[0];
	threads[0].lockB = &all_locks[NUM_THREADS - 1];
	for (int i = 1; i < NUM_THREADS; i++)
	{
		threads[i].num = i;
		threads[i].lockA = &all_locks[i];
		threads[i].lockB = &all_locks[i - 1];
		threads[i].death = &death;
		threads[i].death_lock = &death_lock;
	}

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_create(&threads[i].t_id, NULL, routineA, &threads[i]);

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i].t_id, NULL);

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_mutex_destroy(&all_locks[i]);

	free(threads);
	free(all_locks);
	return (0);
}
