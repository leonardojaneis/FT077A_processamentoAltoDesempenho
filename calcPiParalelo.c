#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUMTHRDS 8
#include <time.h>

	
	/* Referência em computing.llnl/tutorials/pthreads
   	   Example: Using Mutexes 
	*/
	
	// Definição variáveis globais e mutex 
	pthread_t callThd[NUMTHRDS];
	pthread_mutex_t mutexsum;
	static long numsteps = 1000000;
	double sum = 0.0;
	double step;

	// Função calcPi com Mutex 
	void *calcPi(void *arg){

	// Variáveis locais
	int i, len, start, end;
	double x, sumL;
	int offset;
	offset = (int)arg;
	len = (int) numsteps /(int) NUMTHRDS;
	start = offset * len;
	end = (start + len) -1;

	 sumL = 0;
	 for(i=start; i <= end; i++){
	   x = (i+0.5)*step;
	   sumL = sumL + 4.0/(1.0+x*x);
	 }

	 pthread_mutex_lock (&mutexsum);
	 sum = sumL + sum;
	 pthread_mutex_lock (&mutexsum);
	 pthread_exit((void*) 0);
	
}

int main(){
    
	struct timespec begin, end;
    double elapsed;
	int i;
	double pi;
	void *status;
	pthread_attr_t attr;

	pthread_mutex_init(&mutexsum, NULL);
	
	// Criação das threads 
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	step = 1.0/(double) numsteps;
	
	clock_gettime(CLOCK_MONOTONIC, &begin);
	for(i=0; i < NUMTHRDS; i++){

		pthread_create(&callThd[i], &attr, calcPi, (void *)i);

	}
	
	pthread_attr_destroy(&attr);

	// Aguardando outras threads 
	
	for(i=0; i < NUMTHRDS; i++){

		pthread_join(callThd[i], &status);

	}

	// Resultados 
	pi = step * sum;
	clock_gettime(CLOCK_MONOTONIC, &end);
	elapsed = end.tv_sec - begin.tv_sec;
	elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
	printf("Tempo de execucao: 	%f segundos\n", elapsed);
	printf("Valor de pi: %.30f\n", pi);
	pthread_mutex_destroy(&mutexsum);
	pthread_exit(NULL);
	return 0;

}



