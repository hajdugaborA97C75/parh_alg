#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

const int N_THREADS = 10;

void rand_arr_num(int r)
{
    int arr[5] = {1,2,3,4,5};
    printf("%d ", arr[r]);
}

int main()
{
    srand(time(NULL));
    pthread_t threads[N_THREADS];
    int r,i;
    printf(":: Start threads ...\n");
    for (i = 0; i < N_THREADS; ++i) {
        r = rand() % 10 + 1;
        pthread_create(&threads[i], NULL, rand_arr_num, r);
    }
    sleep(1);
    printf(":: Join threads ...\n");
    for (i = 0; i < N_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
