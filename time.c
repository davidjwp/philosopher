#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

long long getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
}

int main() {
    long long startTime, endTime, elapsedTime;

    // Record start time
    startTime = getCurrentTime();

    // Simulate some activity
    usleep(20000);  // Sleep for 2 seconds

    // Record end time
    endTime = getCurrentTime();

    // Calculate elapsed time in milliseconds
    elapsedTime = endTime - startTime;

    printf("Elapsed Time: %lld milliseconds\n", elapsedTime);

    return 0;
}
