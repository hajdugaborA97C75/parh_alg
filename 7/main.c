#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void prime(int x, int n, FILE *f)
{
    int start = x;
    int end = n;
    clock_t difference;
    double sec;
    clock_t before = clock();
    int count,i;
    while(x <= n)
    {
        count = 0;
        i = 2;
        while(i <= x/2)
        {
            if(x%i == 0)
            {
                count++;
                break;
            }
                i++;
            }
        x++;
    }
    difference = clock() - before;
    sec = (double)difference / CLOCKS_PER_SEC;
    fprintf(f, "%d - %d %.3lf \n",start,end,sec);
}

int main()
{
    FILE *f = fopen("test7.txt", "w");
    for(int i = 0;i < 100000;i+=10000)
    {
        prime(i+1,i+10000,f);
    }
    fclose(f);
    return 0;
}
