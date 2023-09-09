
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct __struct_type{
    pthread_t   t_id;
    int         num;
}               t_th;

void    *routine(void *arg)
{
    return(NULL);
}

int main(void)
{
    t_th    th;

    pthread_create(&th.t_id, NULL, routine, &th);
    pthread_join(th.t_id, NULL);
    return (0);
}
