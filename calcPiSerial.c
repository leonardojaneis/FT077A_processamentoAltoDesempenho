#include <stdio.h>
#include <time.h>

float tempo;
time_t t_ini, t_fim;
static long num_steps = 1000000;
double step;
int main ()
{ 
  int i; 
  double x, pi, sum = 0.0;
 
           
  step = 1.0/(double) num_steps;
	clock_t begin = clock();
  for (i=0;i< num_steps; i++)
  {
     x = (i+0.5)*step;
     sum = sum + 4.0/(1.0+x*x);
  }
  pi = step * sum;
  clock_t end = clock();

  printf("Valor de pi: %.30f\n", pi);
  
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Tempo de execucao em segundos: %f\n", time_spent);	

  return 0;
}

