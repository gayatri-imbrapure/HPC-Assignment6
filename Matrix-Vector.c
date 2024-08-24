#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<time.h>
#define N 3  
int main() {
    int i, j;
    int A[N][N], x[N], y[N];
    srand(time(0));
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
        }
        x[i] = rand() % 10;
        y[i] = 0;  
    }
    #pragma omp parallel for private(i, j) shared(A, x, y)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    printf("Resultant Vector y:\n");
    for (i = 0; i < N; i++) {
        printf("%d\n", y[i]);
    }
    return 0;
}
