#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <assert.h>

int SIZE, THRDS;
int **matA, **matB, **matC;


void *multiplica(void *arg)
{
    int pas = (int)arg;
    int start = pas * SIZE/THRDS;
    int stop = (pas+1) * (SIZE/THRDS) - 1;
    int i, j, k;
    for(i = start; i <= stop; i++) {
        for(j = 0; j < SIZE; j++) {
            matC[i][j] = 0;
            for(k = 0; k < SIZE; k++) {
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

void inicializa()
{
    int i, j;

    matA = (int**)malloc(SIZE * sizeof(int *));
    for(i = 0; i < SIZE; i++)
        matA[i] = malloc(SIZE * sizeof(int));

    matB = (int**)malloc(SIZE * sizeof(int *));
    for(i = 0; i < SIZE; i++)
        matB[i] = malloc(SIZE * sizeof(int));

    matC = (int**)malloc(SIZE * sizeof(int *));
    for(i = 0; i < SIZE; i++)
        matC[i] = malloc(SIZE * sizeof(int));

    srand(time(NULL));

    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            matA[i][j] = rand()%100;
            matB[i][j] = rand()%100;
        }
    }
}

int main(int argc, char* argv[])
{	
    struct timespec begin, end;
    double elapsed;		
    pthread_t* threads;
    int rc, i;

    if(argc != 3)
    {
        printf("Uso: %s <tamanho da matriz> <numero de threads\n", argv[0]);
        exit(1);
    }

    SIZE = atoi(argv[1]);
    THRDS = atoi(argv[2]);
    inicializa();
    threads = (pthread_t*)malloc(THRDS * sizeof(pthread_t));

    clock_gettime(CLOCK_MONOTONIC, &begin);

    for(i = 0; i < THRDS; i++) {
        rc = pthread_create(&threads[i], NULL, worker, (void *)i);
        assert(rc == 0);
    }

    for(i = 0; i < THRDS; i++) {
        rc = pthread_join(threads[i], NULL);
        assert(rc == 0);
    } 
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = end.tv_sec - begin.tv_sec;
    elapsed += (end.tv_sec - begin.tv_sec) / 1000000000.0;
    printf("Elapsed time: %.2lf seconds.\n", elapsed);
    for(i = 0; i < SIZE; i++)
    free((void *)matA[i]);
    free((void *)matA);
    for(i = 0; i < SIZE; i++)
    free((void *)matB[i]);
    free((void *)matB);
    for(i = 0; i < SIZE; i++)
    free((void *)matC[i]);
    free((void *)matC);
    free(threads);
    return 0;
}
