#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define N 3  

int main() {
    int i, j, k;
    int A[N][N], B[N][N], C[N][N], C_parallel[N][N];

    srand(time(0));
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;  
            C_parallel[i][j] = 0; 
        }
    }

    // Sequential execution
    double start_time = omp_get_wtime();
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double end_time = omp_get_wtime();
    double seq_time = end_time - start_time;

    start_time = omp_get_wtime();
    #pragma omp parallel for private(i, j, k) shared(A, B, C_parallel) num_threads(10)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                C_parallel[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    double speedup = seq_time / parallel_time;

    printf("Resultant Matrix C (Sequential):\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("\nResultant Matrix C_parallel (Parallel):\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", C_parallel[i][j]);
        }
        printf("\n");
    }

    printf("\nSequential Execution Time: %f seconds\n", seq_time);
    printf("Parallel Execution Time: %f seconds\n", parallel_time);
    printf("Speedup: %f\n", speedup);

    return 0;
}
