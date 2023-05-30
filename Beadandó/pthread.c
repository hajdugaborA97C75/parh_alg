#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <windows.h>

#define R 5000000.0 // A kör sugarának értéke
#define NUM_SIMULATIONS 5 // A szimulációk száma


void* simulate(void* arg) {
	double x = 0.0; // Pont x-koordinátája
    double y = 0.0; // Pont y-koordinátája

   

    while (sqrt(x * x + y * y) < R) {
		int tid = GetCurrentThreadId();
		srand (time(0)+tid);
		
        double x_step = -1.0 + 2.0 * ((double)rand() / RAND_MAX); // Véletlenszerű lépés generálása
        double y_step = -1.0 + 2.0 * ((double)rand() / RAND_MAX); // Véletlenszerű lépés generálása
        x += x_step; // Lépés az x-irányban
        y += y_step; // Lépés az y-irányban
        (*(int*)arg)++;
    }
	
    return NULL;
}

int main() {
	
    pthread_t threads[NUM_SIMULATIONS]; // Párhuzamos szálak
    int steps[NUM_SIMULATIONS] = {0}; // Lépések száma
	
	time_t start,end;
	double total;
	
	start = clock();


    // Szimulációk párhuzamos végrehajtása
    for (int i = 0; i < NUM_SIMULATIONS; i++) {
        pthread_create(&threads[i], NULL, simulate, &steps[i]);
    }

    // Párhuzamos szálak befejezésének várása
    for (int i = 0; i < NUM_SIMULATIONS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Eredmények kiíratása
    for (int i = 0; i < NUM_SIMULATIONS; i++) {
        printf("Simulation %d: %d steps\n", i + 1, steps[i]);
    }

	end = clock();
	total = (double)(end - start) / CLOCKS_PER_SEC;
	printf( "The runtime of the simulation: %.2f seconds.\n", total);
    
	return 0;
}