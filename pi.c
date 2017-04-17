#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

int NUM_OF_THREADS, N;
pthread_mutex_t mutex;
double sum=0.0;
int flag=0;

long time_total(timeval start, timeval end)
{
	long seconds, useconds;

	seconds  = end.tv_sec  - start.tv_sec;

	useconds = end.tv_usec - start.tv_usec;

	return ((seconds) * 1000 + useconds/1000.0) + 0.5;
}


////calculo de PI con busy wainting
void*  Thread_sum_busy_W(void * rank)
{
  int my_rank = *((int*)rank);
  double factor;
  long long i;
  long long my_n=N/NUM_OF_THREADS;
  long long my_first_i=my_n*my_rank;
  long long my_last_i=my_first_i+my_n;
  double my_sum=0.0;

  if((my_first_i%2) ==0)
     factor=1.0;
  else
     factor=-1.0;

  for(i=my_first_i;i<my_last_i;i++,factor=-factor){
    my_sum+=factor/(2*i+1);
  }
  while(flag!=my_rank);
  sum+=my_sum;
  flag=(flag+1)%NUM_OF_THREADS;

}



///calculo de pi con mutex
void*  Thread_sum_mutex(void * rank)
{
  int my_rank = *((int*)rank);
  double factor;
  long long i;
  long long my_n=N/NUM_OF_THREADS;
  long long my_first_i=my_n*my_rank;
  long long my_last_i=my_first_i+my_n;
  double my_sum=0.0;

  if((my_first_i%2) ==0)
     factor=1.0;
  else
     factor=-1.0;

  for(i=my_first_i;i<my_last_i;i++,factor=-factor){
    my_sum+=factor/(2*i+1);
  }

  pthread_mutex_lock(&mutex);
  sum+=my_sum;
  pthread_mutex_unlock(&mutex);

}

int main(int argc, char* argv[]){

		N = atoi(argv[1]);
	 	NUM_OF_THREADS = atoi(argv[2]);

    timeval start;
    timeval end;
    long final_par;
    	srand(time(NULL));
	int i;

	pthread_t* threads = (pthread_t *)malloc(NUM_OF_THREADS * sizeof(pthread_t));



  // Creamos los threads
	gettimeofday(&start, 0);

	for(i = 0; i < NUM_OF_THREADS; i++){
		pthread_create(&threads[i], NULL,Thread_sum_busy_W,&i);
    pthread_join(threads[i], NULL);
  }


	gettimeofday(&end, 0);
  final_par = time_total(start, end);
  fprintf(stdout, "TIEMPO CONC.:%d mseg\n",(int) final_par);

	free(threads);

}
