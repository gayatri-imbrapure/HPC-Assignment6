#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define N 3  

int main() {
    int i, j;
    int A[N][N], x[N], y[N], y_parallel[N];
    srand(time(0));
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
        }
        x[i] = rand() % 10;
        y[i] = 0;  
        y_parallel[i] = 0; 
    }
    double start_time = omp_get_wtime();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    double end_time = omp_get_wtime();
    double seq_time = end_time - start_time;
    start_time = omp_get_wtime();
    #pragma omp parallel for private(i, j) shared(A, x, y_parallel) num_threads(5)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            y_parallel[i] += A[i][j] * x[j];
        }
    }
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    double speedup = seq_time / parallel_time;
    printf("Resultant Vector y (Sequential):\n");
    for (i = 0; i < N; i++) {
        printf("%d\n", y[i]);
    }
    printf("\nResultant Vector y_parallel (Parallel):\n");
    for (i = 0; i < N; i++) {
        printf("%d\n", y_parallel[i]);
    }
    printf("\nSequential Execution Time: %f seconds\n", seq_time);
    printf("Parallel Execution Time: %f seconds\n", parallel_time);
    printf("Speedup: %f\n", speedup);
    return 0;
}
