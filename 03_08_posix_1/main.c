#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

const int N_THREADS = 2;


void create_thread(pthread_t threads[])
{
    pthread_create(&threads[1], NULL, sleep, 4);
    sleep(8);
}

int main(int argc, char* argv[])
{
    pthread_t threads[N_THREADS];
    pthread_create(&threads[0], NULL, create_thread, threads);
    int i;
    for (i = 0; i < N_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    printf(":: Ready.\n");

    return 0;
}
