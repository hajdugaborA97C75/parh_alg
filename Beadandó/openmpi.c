#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define R 10000.0 // A kör sugarának értéke
#define NUM_SIMULATIONS 5 // A szimulációk száma

int main() {
	FILE *file;
	file = fopen("openmpi.csv", "a");
	
    int steps[NUM_SIMULATIONS] = {0}; // Lépések száma

	time_t start,end;
	double total;
	
	start = clock();
	
    #pragma omp parallel
    {
		int tid = omp_get_thread_num();
		srand (time(0)+tid);

        #pragma omp for
        for (int i = 0; i < NUM_SIMULATIONS; i++) {
            double x = 0.0; // Pont x-koordinátája
            double y = 0.0; // Pont y-koordinátája

            while (sqrt(x * x + y * y) < R) {
                double x_step = -1.0 + 2.0 * ((double)rand() / RAND_MAX); // Véletlenszerű lépés generálása
				double y_step = -1.0 + 2.0 * ((double)rand() / RAND_MAX); // Véletlenszerű lépés generálása
				x += x_step; // Lépés az x-irányban
				y += y_step; // Lépés az y-irányban
                steps[i]++;
            }
        }
    }

    // Eredmények kiíratása
    for (int i = 0; i < NUM_SIMULATIONS; i++) {
        fprintf(file,"%d,",steps[i]);
    }

	end = clock();
	total = (double)(end - start) / CLOCKS_PER_SEC;
	
	fprintf(file,"%d,%.2f\n", (int)R, total);
	
	fclose(file);
	
    return 0;
}
