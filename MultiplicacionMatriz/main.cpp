#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void crear_matriz(int **&A,int f,int c)
{

    A = (int **)malloc (f*sizeof(int *));

    for (int i=0;i<f;i++)
    A[i] = (int *) malloc (c*sizeof(int));
}


void llenar_matriz(int **&A,int f,int c)
{

    for(int i=0;i<f;i++)
    {
        for(int j=0;j<c;j++)
        {
            A[i][j]=rand()%10;

        }
    }
}


void mostrar_matriz(int **&A,int f,int c)
{
     printf("\n");
    for(int i=0;i<f;i++)
    {
        for(int j=0;j<c;j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}



int main( )
{
  int af=3, ac=3, bf=3, bc=2;

  int **A, **B, **C;
  crear_matriz(A,af,ac); llenar_matriz(A,af,ac);
   printf("\n");
  crear_matriz(B,bf,bc); llenar_matriz(B,bf,bc);
  crear_matriz(C,af,bc);


  for(int i=0;i<af;i++){
      for(int j=0;j<bc;j++){
          C[i][j]=0;
          for(int k=0;k<ac;k++){
              C[i][j]=(C[i][j]+(A[i][k]*B[k][j]));
          }
      }
  }

  mostrar_matriz(A,af,ac);
  mostrar_matriz(B,bf,bc);
mostrar_matriz(C,af,bc);


}
