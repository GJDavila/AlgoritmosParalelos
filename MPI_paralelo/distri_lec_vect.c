#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>

///--mpicc distri_lec_vect.c -o  distri_lec_vect
///--mpirun -np 5 ./distri_lec_vect



void Read_vector(double local_a[], int local_n, int n, char vec_name[], int my_rank, MPI_Comm comm){
  double* a = NULL;
  int i;

  if(my_rank == 0){
    a = malloc(n*sizeof(double));
    printf("Ingrese los valores del vector %s\n", vec_name);
    for(i = 0; i < n; i++)
      {scanf("%lf", &a[i]);}

     printf("Vector dividido en \n");
     MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n, MPI_DOUBLE,0,comm);
     for(i = 0; i < local_n; i++){
       printf("%f ", local_a[i]);
     } printf("\n ");
     free(a);

  }
  else{
      MPI_Scatter(a,local_n,MPI_DOUBLE,local_a,local_n,MPI_DOUBLE,0,comm);
      for(i = 0; i < local_n; i++){
        printf("%f ", local_a[i]);
      } printf("\n ");
  }
}

void Print_vector(double local_b[], int local_n, int n, char title[], int my_rank, MPI_Comm comm){
  double* b = NULL;
  int i;
  if(my_rank == 0){
    b = malloc(n*sizeof(double));
    MPI_Gather(local_b, local_n, MPI_DOUBLE,b,local_n, MPI_DOUBLE,0,comm);
    printf("%s\n", title);
    for(i = 0; i < n; i++){
      printf("%f ", b[i]);
    }
    printf("\n");
    free(b);
  }
  else{
    MPI_Gather(local_b, local_n, MPI_DOUBLE, b, local_n, MPI_DOUBLE, 0, comm);
  }
}


int main(){

  int comm_sz;
  int my_rank;

  MPI_Init(NULL,NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int local_n=2;/// tamaño de los bloques que tendra cada proceso al repartirlos
  int n=10;  ///numero de elementos del Vector
  double local_a[local_n];
  char vec_name[10];

  Read_vector(local_a,local_n,n,"Vector inicial",my_rank,MPI_COMM_WORLD);

  Print_vector(local_a,local_n,n,"Vector reconstruido", my_rank,MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}
