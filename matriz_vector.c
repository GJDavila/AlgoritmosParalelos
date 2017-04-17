#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

int NUM_OF_THREADS, M, N;

/*
	Utilizaremos variables globales para simplificar
	el paso de parametros hacia pthread_create
*/

float* A;
float* x;
float* y;
pthread_mutex_t mutex;



long time_total(timeval start, timeval end)
{
	long seconds, useconds;

	seconds  = end.tv_sec  - start.tv_sec;

	useconds = end.tv_usec - start.tv_usec;

	return ((seconds) * 1000 + useconds/1000.0) + 0.5;
}

void LLenar_matriz(float A[], int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
  {  	for (j = 0; j < cols; j++)
    		{
					A[i * cols + j] = (rand() % 100);
				}
	}
}

void LLenar_vector(float x[], int rows)
{
	int i;
	for (i = 0; i < rows; i++)
		x[i] = (rand() % 100);
}

void print_M(float A[], int rows, int cols) {
   int	i, j;

   for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++)
      {
	   printf("%f  ", A[i*cols + j]);

      }
      printf("\n");
   }
}

void print_V(float x[], int rows) {
   int   i;

   for (i = 0; i < rows; i++)
      printf("%f  ", x[i]);
   printf("\n");
}


///paralela concurrente
void *matriz_vector_paralelo(void* rank) {
   	int whoami = *(int *) rank;
    int from = whoami * M / NUM_OF_THREADS;
    int to = from + (M / NUM_OF_THREADS) - 1;
    int i, j;
	for (i = from; i <= to; i++) {
	  y[i] = 0.0;
	  for (j = 0; j < M; j++){
	 //	pthread_mutex_lock(&mutex);
			y[i] += A[i*M+j]*x[j];
	 	//	pthread_mutex_unlock(&mutex);
          }
	}
   return NULL;
}




int main(int argc, char* argv[]){

		M = atoi(argv[1]);
		N = atoi(argv[2]);
		NUM_OF_THREADS = atoi(argv[3]);

	int i;

	pthread_t* threads = (pthread_t *)malloc(NUM_OF_THREADS * sizeof(pthread_t));

	A = (float *) malloc(M * N * sizeof(float));
	x = (float *) malloc(N * sizeof(float));
	y = (float *) malloc(M * sizeof(float));

	LLenar_matriz(A, M, N);
	LLenar_vector(x, N);

	// Creamos los threads

	for(i = 0; i < NUM_OF_THREADS; i++)
		pthread_create(&threads[i], NULL,matriz_vector_paralelo, &i);


	for (i = 0; i < NUM_OF_THREADS; i++)
		pthread_join(threads[i], NULL);

	free(A);
	free(x);
	free(y);
	free(threads);
}
