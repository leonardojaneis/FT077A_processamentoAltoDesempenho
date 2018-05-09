#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <omp.h>
#define MATRIX_SIZE 1000


//Código com referência de OpenMp Example - Matrix Multiply - C Version de Blaise Barney

int main(int argc, char *argv[])
{
	int tid;
	int chunk = 10;
	double **a;
	double **b;
	double **c;
	double **d;
	struct timeval t1, t2;
	double elapsed_time;
	int i, j, k, nthreads = 32;
	
	a = malloc(MATRIX_SIZE * sizeof(double *));
	b = malloc(MATRIX_SIZE * sizeof(double *));
	c = malloc(MATRIX_SIZE * sizeof(double *));
	d = malloc(MATRIX_SIZE * sizeof(double *));
	
	for(i = 0; i < MATRIX_SIZE; i++)
	{
		a[i] = malloc(MATRIX_SIZE * sizeof(double));
		b[i] = malloc(MATRIX_SIZE * sizeof(double));
		c[i] = malloc(MATRIX_SIZE * sizeof(double));
		d[i] = malloc(MATRIX_SIZE * sizeof(double));
	}	
	
	for(i = 0; i < MATRIX_SIZE; i++)
	{
		for(j = 0; j < MATRIX_SIZE; j++)
		{
			a[i][j] = rand()%100;
			b[i][j] = rand()%100;
			c[i][j] = rand()%100;
		}
	}
	
	gettimeofday(&t1, NULL);
	omp_set_num_threads(nthreads);
	
	#pragma omp parallel shared(a,b,c,d, nthreads, chunk) private(tid, i, j, k)
	{
		tid = omp_get_thread_num();
		
		if (tid == 0)
		{
			nthreads = omp_get_num_threads();
			printf("Iniciando programa com %d threads\n",nthreads);
		}
		#pragma omp for schedule (static, chunk)
		
		for (i=0; i< MATRIX_SIZE; i++)    
		{
			printf("Thread=%d opera na linha=%d\n",tid,i);
			for(j=0; j<MATRIX_SIZE; j++)       
			  for (k=0; k<MATRIX_SIZE; k++){
				d[i][j] += a[i][k] * b[k][j];
			  }
				d[i][j] += c[i][j];
		}
	
	}   
	gettimeofday(&t2, NULL);
	elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0;      // segundos para milissegundos
	elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0;   // microssegundos para milissegundos
	printf("Tempo utilizado com a utilizaçao de threads: %f milissegundos\n", elapsed_time); 
	//FIM
}