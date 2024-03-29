#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <windows.h>

#define R 10000.0 // A kör sugarának értéke
#define NUM_SIMULATIONS 5 // A szimulációk száma


void* simulate(void* arg) {
	double x = 0.0; // Pont x-koordinátája
    double y = 0.0; // Pont y-koordinátája
	
	int tid = GetCurrentThreadId();
	srand (time(0)+tid);

    while (sqrt(x * x + y * y) < R) {
		
        double x_step = -1.0 + 2.0 * ((double)rand() / RAND_MAX); // Véletlenszerű lépés generálása
        double y_step = -1.0 + 2.0 * ((double)rand() / RAND_MAX); // Véletlenszerű lépés generálása
        x += x_step; // Lépés az x-irányban
        y += y_step; // Lépés az y-irányban
        (*(int*)arg)++;
    }
	
    return NULL;
}

int main() {
	FILE *file;
	file = fopen("pthread.csv", "a");
	
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
        fprintf(file,"%d,", steps[i]);
    }

	end = clock();
	total = (double)(end - start) / CLOCKS_PER_SEC;
	
	fprintf(file,"%d,%.2f\n", (int)R, total);
	
	fclose(file);
	
	return 0;
}