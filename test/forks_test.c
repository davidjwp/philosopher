#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

typedef struct _thread_struc {
    pthread_t t_id;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    pthread_mutex_t fork_lock;
    int *sharedData;
    int t_num;
} t_thread;

void *accessing(t_thread *th) {
    pthread_mutex_lock(&th->fork_lock);
    pthread_mutex_lock(th->l_fork);
    printf("Thread %d has picked up the left fork\n", th->t_num);
    pthread_mutex_lock(th->r_fork);
    printf("Thread %d has picked up the right fork\n", th->t_num);
    *(th->sharedData)++;
    printf("Thread %d is accessing the shared data\n", th->t_num);
    usleep(1000);
    printf("Thread %d is dropping both forks\n", th->t_num);
    pthread_mutex_unlock(th->r_fork);
    pthread_mutex_unlock(th->l_fork);
    pthread_mutex_unlock(&th->fork_lock);
    return NULL;
}

void *routine(void *arg) {
    t_thread *th = (t_thread *)arg;
    if (th->t_num % 2 == 0)
        usleep(1000);
    return accessing(th);
}

int main(void) {
    pthread_mutex_t *forks;
    t_thread *th;
    int sharedData = 0;
    int i = 0;

    forks = malloc(sizeof(pthread_mutex_t) * NUM_THREADS);
    th = malloc(sizeof(t_thread) * NUM_THREADS);

    i = 0;
    while (i < NUM_THREADS) {
        pthread_mutex_init(&th[i].fork_lock, NULL);
        pthread_mutex_init(&forks[i], NULL);
        th[i].l_fork = &forks[i];
        if (i == NUM_THREADS - 1)
            th[i].r_fork = &forks[0];
        else
            th[i].r_fork = &forks[i + 1];
        th[i].t_num = i + 1;
        th[i].sharedData = &sharedData;
        i++;
    }

    i = 0;
    while (i < NUM_THREADS) {
        pthread_create(&th[i].t_id, NULL, routine, &th[i]);
        i++;
    }

    i = 0;
    while (i < NUM_THREADS) {
        pthread_join(th[i].t_id, NULL);
        i++;
    }

    i = 0;
    while (i < NUM_THREADS) {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }

    free(th);
    free(forks);

    return 0;
}
