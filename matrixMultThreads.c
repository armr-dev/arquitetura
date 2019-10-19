#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADS_QTY 1
#define N 2000

static int mat1[N][N] = {{1,2},{2,1}}, mat2[N][N] = {{1,2},{2,1}}, res[N][N], passo;


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

void *multiplyThreads(void* args) {
    int thread = passo++;

    for(int i = thread * N / THREADS_QTY; i < (thread+1) * N / THREADS_QTY; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                res[i][j] = mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main() { 
    srand(time(NULL));
  
    double tempoLevado;
    pthread_t threads[N];

    clock_t t;

    createMatrix(mat1);
    createMatrix(mat2);

    t = clock();

    for (int i = 0; i < THREADS_QTY; i++) {
        int* p;
        pthread_create(&threads[i], NULL, multiplyThreads, (void *)p);
    }

    for (int i = 0; i < THREADS_QTY; i++) {
        pthread_join(threads[i], NULL);
    }

    t = clock() - t;
    tempoLevado = (((double)t)/CLOCKS_PER_SEC)/THREADS_QTY;
    printf("%f + ", tempoLevado);

    return 0; 
} 