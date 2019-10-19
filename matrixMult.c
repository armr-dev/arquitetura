#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 400

void multiply(int mat1[][N], int mat2[][N], int res[][N]) { 
    int i, j, k; 
    for (i = 0; i < N; i++) 
    { 
        for (j = 0; j < N; j++) 
        { 
            res[i][j] = 0; 
            for (k = 0; k < N; k++) 
                res[i][j] += mat1[i][k]*mat2[k][j]; 
        } 
    } 
} 
  
void createMatrix(int matrix[N][N]) {
    int value;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            value = rand()%100;
            matrix[i][j] = value;
        }
    }
}

int main() { 
    srand(time(NULL));
  
    int mat1[N][N], mat2[N][N];

    createMatrix(mat1);
    createMatrix(mat2);

    int res[N][N]; // To store result 
    int i, j; 
    clock_t t;
    t = clock();
    multiply(mat1, mat2, res); 
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    // printf("Result matrix is \n"); 
    // for (i = 0; i < N; i++) 
    // { 
    //     for (j = 0; j < N; j++) 
    //        printf("%d ", res[i][j]); 
    //     printf("\n"); 
    // } 

    printf("Tempo que levou: %f\n", time_taken);
  
    return 0; 
} 