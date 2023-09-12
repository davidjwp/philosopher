// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>

// # include <unistd.h>
// # include <sys/time.h>

// #define NUM_THREADS 1

// // // Define a structure to hold thread-specific data
// typedef struct {

//     pthread_mutex_t *sharedMutex;
//     pthread_t   t_id;
//     long threadId;
//     int *sharedData;
// } ThreadData;

// void *threadFunction(void *arg) {
//     ThreadData *data = (ThreadData *)arg;

//     // Access the thread-specific data
//     pthread_mutex_t *sharedMutex = data->sharedMutex;
//     long id = data->threadId;

//     // Attempt to lock the shared mutex
//     pthread_mutex_lock(sharedMutex);
//     printf("Thread %ld locked the mutex.\n", id);
//     // Simulate some work
//     usleep(100000);  // Sleep for 100 milliseconds

//     // Unlock the mutex
//     pthread_mutex_unlock(sharedMutex);
//     printf("Thread %ld unlocked the mutex.\n", id);

//     pthread_exit(NULL);
// }

// int main() {
//     pthread_mutex_t sharedMutex;
//     int sharedData = 1;
//     int i;

//     pthread_mutex_init(&sharedMutex, NULL);
//     // Create an array to hold thread-specific data
//     ThreadData *threadData = malloc(sizeof(ThreadData) * NUM_THREADS);


//     for (i = 0; i < NUM_THREADS; i++) {
//         // Initialize thread-specific data
//         threadData[i].sharedMutex = &sharedMutex;
//         threadData[i].threadId = i + 1;
//         threadData[i].sharedData = &sharedData;
//         if (pthread_create(&threadData[i].t_id, NULL, threadFunction, (void *)&threadData[i]) != 0) {
//             fprintf(stderr, "Error creating thread %d\n", i);
//             exit(1);
//         }
//     }

//     for (i = 0; i < NUM_THREADS; i++) {
//         pthread_join(threadData[i].t_id, NULL);
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

# include <unistd.h>
# include <sys/time.h>

#define NUM_THREADS 1

// // Define a structure to hold thread-specific data
typedef struct {

    pthread_mutex_t *sharedMutex;
    pthread_t   t_id;
    long threadId;
    int *sharedData;
} ThreadData;

void	*threadFunction(void *arg)
{

}

int main(void)
{
	pthread_mutex_t	sharedMutex;
	int	sharedData = 1;

	pthread_mutex_init(&sharedMutex, NULL);
	ThreadData	*threadData = malloc(sizeof(ThreadData) * NUM_THREADS);

	for (int i = 0; i < NUM_THREADS; i++)
	{
		threadData[i].sharedMutex = &sharedMutex;
		threadData[i].threadId = i;
		threadData[i].sharedData = &sharedData;
		if (pthread_create(&threadData[i].t_id, NULL, threadFunction, (void *)&threadData[i]) != 0)
		{
			fprintf(stderr, "Error creating thread %d\n", i);
			exit(1);
		}
	}
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(threadData[i].t_id, NULL);
	free(threadData);
	return (0);
}