#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADS_QTY 8                                // Define a quantidade de threads do programa.
#define N 2000                                       // Define o tamanho da matriz.

static int mat1[N][N], mat2[N][N], res[N][N], passo; // Inicializa as matrizes como variáveis globais.

/*
    função: cria N*N número aleatórios para preencher a matrix de entrada
        input: int matrix[N][N] - matriz que receberá os valores gerados.
*/
void createMatrix(int matrix[N][N]) {
    int value;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            value = rand()%100;
            matrix[i][j] = value;
        }
    }
}

/*  função: divide a matriz em partes menores (baseado na quantidade de threads), 
            multiplica as linhas e colunas e atribui o resultado à matriz res.
*/
void *multiplyMatrix() {
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
    
    double tempoLevado;         // Armazena o tempo que leva para executar os algoritmos
    pthread_t threads[N];       // Armazena as threads criadas

    clock_t t;                  // Variável de tempo

    // Atribui valores aleatórios às matrizes a serem multiplicadas.
    createMatrix(mat1);
    createMatrix(mat2);

    // Atribui o valor do relógio no momento de início de execução do algoritmo
    t = clock();

    // Cria as threads que executam a função multiplyMatrix
    for (int i = 0; i < THREADS_QTY; i++) {
        int* p;
        pthread_create(&threads[i], NULL, multiplyMatrix, NULL);
    }

    // Espera todas as threads finalizarem
    for (int i = 0; i < THREADS_QTY; i++) {
        pthread_join(threads[i], NULL);
    }

    // Mede o tempo levado pelo programa e imprime na tela.
    t = clock() - t;
    tempoLevado = (((double)t)/CLOCKS_PER_SEC)/THREADS_QTY;
    printf("%f\n", tempoLevado);

    return 0; 
} 