#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

const int N_THREADS = 60;


void wait_random_time(void* _)
{
    pthread_t tid;
    tid = pthread_self();
    printf("[%d] Wait %d seconds ...\n", (int)&tid, 1);
    sleep(1);
    printf("[%d] Ready!\n", (int)&tid);
}


int main(int argc, char* argv[])
{
    pthread_t threads[N_THREADS];
    int i;
    printf(":: Start threads ...\n");
    for (i = 0; i < N_THREADS; ++i) {
        pthread_create(&threads[i], NULL, wait_random_time, NULL);
    }

    printf(":: Join threads ...\n");
    for (i = 0; i < N_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf(":: Ready.\n");

    return 0;
}

