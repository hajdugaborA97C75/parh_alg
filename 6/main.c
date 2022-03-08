#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));
    int x = rand()%(0 - 11);
    int y = rand()%(0 - 11);
    int result = x + y;
    int input;
    int wrong = 1;
    clock_t difference;
    double sec;
    printf("Enter the result of %d + %d\n", x, y);
    clock_t before = clock();
    scanf("%d", &input);
    if(input == result){
        printf("Good!\n");
        difference = clock() - before;
        wrong = 0;
    }
    while(wrong){
        printf("Try again: ");
        scanf("%d", &input);
        if(input == result){
            printf("Good!\n");
            difference = clock() - before;
            wrong = 0;
        }
    }
    sec = (double)difference / CLOCKS_PER_SEC;
    printf("Time to answer: %.3lf seconds",sec);
    return 0;
}
