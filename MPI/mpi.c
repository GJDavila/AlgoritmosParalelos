
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define BUFSIZE 128
#define TAG 0

int main(int argc, char *argv[])
{


  int numprocs;
  int myid;


  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);


  int pelota=0;
  int pelota_final=10;

  if(myid==0)
  {
    if(pelota<pelota_final)
    {
      printf("proceso %d tiene %d \n",myid,pelota );
      //enviar
      pelota++;
      MPI_Send(&pelota, 4, MPI_INT, 1, 0, MPI_COMM_WORLD);
      printf("proceso %d envia  %d \n",myid,pelota );
    }
  }


  while(pelota<pelota_final)
  {


      if(myid==1)
      {
         MPI_Recv(&pelota, 4, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
         printf("proceso %d recibe  %d \n",myid,pelota );

          if (pelota<pelota_final) {
            pelota++;
            MPI_Send(&pelota, 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
            printf("proceso %d envia  %d \n",myid,pelota );
         }

       }

       if(myid==0)
       {
         MPI_Recv(&pelota, 4, MPI_INT, 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
         printf("proceso %d recibe  %d \n",myid,pelota );
          if (pelota<pelota_final) {
            pelota++;
            MPI_Send(&pelota, 4, MPI_INT, 1, 0, MPI_COMM_WORLD);
            printf("proceso %d envia  %d \n",myid,pelota );
          }
       }


    }

  MPI_Finalize();
  return 0;
}
