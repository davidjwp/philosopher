
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct _blablat{
    pthread_mutex_t rightlock;
    pthread_mutex_t leftlock;
    pthread_t t_id;
    int num;
}               struct_t;

void    *routine(void *arg)
{
    struct_t *str;

    str = (struct_t *)arg;
    if (str->num == 1)
        usleep(1000);
    if (!pthread_mutex_lock(&str->rightlock))
    {
        printf("thread %i pass \n", str->num);
        pthread_mutex_unlock(&str->rightlock);
    }
    else 
        return (0);
    // if (!pthread_mutex_lock(&str->rightlock) && !pthread_mutex_lock(&str->rightlock))
    // {
    //     pthread_mutex_unlock(&str->rightlock);
    //     pthread_mutex_unlock(&str->leftlock);
    //     printf("thread %i pass \n", str->num);
    // }
    return ((void *)0);
}

int main(void)
{
    struct_t *str;
    pthread_mutex_t *forks;

    str = (struct_t *)malloc(sizeof(struct_t) * 2);
    if (str == NULL)
        return (printf("malloc fail\n"), 0);
    for (int i = 0; i < 0; i++)
    {
        
    }
    for (int i = 0; i < 2; i++)
    {
        str[i].num = i;
        pthread_create(&str[i].t_id, NULL, routine, &str[i]);
    }
    for (int i = 0; i < 2; i++)
        pthread_join(str[i].t_id, NULL);
    free(str);
}

/*use this to test the same setup and see where you mess up, it's clearer*/

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>

// typedef struct {
//     pthread_t thread_id;
//     pthread_mutex_t mutex;
//     int thread_num;
// } ThreadData;

// void* thread_routine(void* arg) {
//     ThreadData* data = (ThreadData*)arg;

//     // Access data specific to this thread
//     pthread_mutex_lock(&data->mutex);
//     printf("Thread %d is running\n", data->thread_num);
//     pthread_mutex_unlock(&data->mutex);

//     return NULL;
// }

// int main() {
//     int num_threads = 4; // Change this to the desired number of threads

//     ThreadData* threads = (ThreadData*)malloc(num_threads * sizeof(ThreadData));
//     if (threads == NULL) {
//         perror("Failed to allocate memory");
//         exit(EXIT_FAILURE);
//     }

//     // Initialize and create threads
//     for (int i = 0; i < num_threads; i++) {
//         threads[i].thread_num = i;
//         if (i != num_threads)
//             pthread_mutex_init(&threads[i].mutex, NULL);
//         pthread_create(&threads[i].thread_id, NULL, thread_routine, &threads[i]);
//     }

//     // Wait for threads to finish
//     for (int i = 0; i < num_threads; i++) {
//         pthread_join(threads[i].thread_id, NULL);
//         pthread_mutex_destroy(&threads[i].mutex);
//     }

//     free(threads);

//     return 0;
// }
