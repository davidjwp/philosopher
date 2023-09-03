#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t initializedMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t uninitializedMutex; // Not initialized

void *threadFunction(void *arg) {
    pthread_mutex_t *mutexToLock = (pthread_mutex_t *)arg;

    if (pthread_mutex_lock(mutexToLock) == 0) {
        printf("Thread acquired the lock.\n");
        // ... perform some work ...
        pthread_mutex_unlock(mutexToLock);
        printf("Thread released the lock.\n");
    } else {
        printf("Thread failed to acquire the lock.\n");
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, threadFunction, &initializedMutex);
    pthread_create(&thread2, NULL, threadFunction, &uninitializedMutex);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    

    return 0;
}
