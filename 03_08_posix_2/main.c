#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int arr[1000];
int count = 0;
const int N_THREADS = 10;

void prime_in_interval(int number1)
{
    int i,j,flag;
    int number2 = number1 + 99;
    for(i=number1+1;i<number2;i++){// interval between two numbers
        flag=0;
        for(j=2;j<=i/2;++j){ //checking number is prime or not
            if(i%j==0){
                flag=1;
                break;
            }
        }
        if(flag==0)
            {
                arr[count] = i;
                count++;
            }
   }
   return 0;
}

int main()
{
    pthread_t threads[N_THREADS];
    int i;
    int interval_start = 0;
    printf(":: Start threads ...\n");
    for (i = 0; i < N_THREADS; ++i) {
        pthread_create(&threads[i], NULL, prime_in_interval, interval_start);
        interval_start += 100;
    }

    printf(":: Join threads ...\n");
    for (i = 0; i < N_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    i = 0;
    while(arr[i] != 0)
    {
        printf("%d ", arr[i]);
        i++;
    }
    return 0;
}
