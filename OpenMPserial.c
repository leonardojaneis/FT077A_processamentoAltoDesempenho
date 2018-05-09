#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdio.h> 
#include<stdlib.h>
#define MATRIZ_SIZE 1000

void printMatriz(int** matriz){

for(int i=0; i<MATRIZ_SIZE;i++)
      {
          printf("\n");
          for(int j=0;j<MATRIZ_SIZE;j++)
          {
              printf("%d\t",matriz[i][j]);
          }
      }
}

 int** lerMatriz(char* fileName)
 {

    FILE *arq;
    int** matriz;
    matriz = malloc(sizeof(int*)*MATRIZ_SIZE);
    int i=0;
    int j=0;

   if (fileName == NULL)
   {
        fprintf(stderr,"File name cannot be null\n");
        exit(EXIT_FAILURE);
   }
   for(i=0;i<MATRIZ_SIZE;i++)
   { 
         matriz[i]=malloc(sizeof(int)*MATRIZ_SIZE);
            if(matriz[i] == NULL)
            {
                  fprintf(stderr, "out of memory\n");
                  exit(0);
            }
   }
 
   arq = fopen(fileName,"r");

   if (arq == NULL)
   {
   	      perror("I cannot open file to read\n");
   	      exit(EXIT_FAILURE);
   }

   for(int k=0;k<MATRIZ_SIZE;k++)
   {
     for(j=0;j<MATRIZ_SIZE;j++)
     {
         int arquivo;
         fscanf(arq,"%d",&arquivo);
         matriz[k][j] = arquivo;
     }
   }
 fclose(arq);
 return matriz;
}
 
int** multMat(int** matriz1,  int** matriz2, int** matriz3)
{
     int** resultado;
     resultado = malloc(sizeof(int*)*MATRIZ_SIZE);
     for(int i=0;i<MATRIZ_SIZE;i++)
     {
          resultado[i] = malloc(sizeof(int)*MATRIZ_SIZE);
     }
	 
     for (int i=0;i<MATRIZ_SIZE;i++)
     {
         for(int j=0;j<MATRIZ_SIZE;j++)
         {
	     int resultT = 0;
             int resultP = 0;
             for(int k=0;k<MATRIZ_SIZE;k++)
             {
                int mat1 = matriz1[i][k];
                int mat2 = matriz2[k][j];
		int mat3 = matriz[i][j];
                int mult = mat1*mat2;
                resultP = resultP + mult;
		resultT = resultP + mat3;
              }
            resultado[i][j] = resultT;
        }
 
     }
      return resultado;
}
 
int main()
{
      char* fileName1 = "matriz1.txt";
      char* fileName2 = "matriz2.txt";
      char* fileName3 = "matriz3.txt";
      int** matriz1;
      int** matriz2;
      int** matriz3;
      int** resultado;
      matriz1 = lerMatriz(fileName1);
      matriz2 = lerMatriz(fileName2);
      matriz3 = lerMatriz(fileName3);
      clock_t begin = clock();
      resultado = multMat(matriz1, matriz2, matriz3);
      clock_t end = clock();
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("Tempo de execucao: %f\n", time_spent);	
      //printMatriz(resultado);
      return 0;
}


