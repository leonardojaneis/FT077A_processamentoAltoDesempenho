#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define MATRIX_SIZE 1000

int a[MATRIX_SIZE][MATRIX_SIZE];
int b[MATRIX_SIZE][MATRIX_SIZE];
int c[MATRIX_SIZE][MATRIX_SIZE];
int d[MATRIX_SIZE][MATRIX_SIZE];

void alocarValores(){	
	for(int i = 0; i < MATRIX_SIZE; i++)
		for(int j = 0; j < MATRIX_SIZE; j++)
			a[i][j] = rand()%100;
			b[i][j] = rand()%100;
			d[i][j] = rand()%100;
}

/*
void print(int a[MATRIX_SIZE][MATRIX_SIZE]){
	
	for(i = 0; i < MATRIX_SIZE; i++){
		printf("\n\t|");
		for(int j = 0; j < MATRIX_SIZE; j++)
		printf("%2d", a[i][j]);
		printf("|");
	}	
}
*/

int main(int argc, char* argv[]){
	
	double start, finish;
	int procs, rank, begin, end;
	int i, j, k;
	int d[MATRIX_SIZE][MATRIX_SIZE];
	
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &procs);	
	
	if(MATRIX_SIZE % procs != 0){
		if(rank == 0) printf("A matriz precisa ser divisivel pelo numero de processos");
			MPI_Finalize();
		    exit(-1);
	}
	start=MPI_Wtime();	
	
	begin = rank * MATRIX_SIZE / procs;
	end = (rank + 1) * MATRIX_SIZE / procs;
	
	if(rank == 0){
		alocarValores();
	}
	
	
	MPI_Bcast(b, MATRIX_SIZE*MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(c, MATRIX_SIZE*MATRIX_SIZE/procs, MPI_INT, c[begin], MATRIX_SIZE*MATRIX_SIZE/procs, MPI_INT, 0, MPI_COMM_WORLD);
	
	
	for(i = begin; i < end; i++)
		for (j = 0; j < MATRIX_SIZE; j++){
			for (k = 0; k < MATRIX_SIZE; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
				c[i][j] += d[i][j];
		}
	
	
	MPI_Gather(c[begin], MATRIX_SIZE*MATRIX_SIZE/procs, MPI_INT, c, MATRIX_SIZE*MATRIX_SIZE/procs, MPI_INT, 0, MPI_COMM_WORLD);
	finish=MPI_Wtime();
	MPI_Finalize();
	printf("Tempo de execucao por processp: %f segundos\n", finish-start);
	return 0;
}