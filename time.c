#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

long long getcurrenttime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
}

int main() {
    long long startTime, endTime, elapsedTime;

    // Record start time
    startTime = getcurrenttime();

    // Simulate some activity
    usleep(500000);  // Sleep for 2 seconds

    printf ("Elapsed Time: %lld milliseconds\n", getcurrenttime() -startTime);
    // Record end time
    // endTime = getcurrenttime();

    // Calculate elapsed time in milliseconds
    // elapsedTime = endTime - startTime;

    // printf("Elapsed Time: %lld milliseconds\n", elapsedTime);

    return 0;
}