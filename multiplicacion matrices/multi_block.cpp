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

int n=1000;
int blockSize=50;
void BlockMultiplication(int **&A,int **&B,int **&C)
{

    for(int i=0; i<n; i+=blockSize)
        for(int j=0; j<n; j+=blockSize)
            for(int k=0; k<n; k+=blockSize)
                for(int x=i; x<i+blockSize; ++x)
                    for(int y=j; y<j+blockSize; ++y)
                        for(int z=k; z<k+blockSize; ++z)
                        {
                            C[x][y]+=A[x][z]*B[z][y];
                        }

}


 

int main( )
{
  int af=n, ac=n, bf=n, bc=n;

  int **A, **B, **C;

  crear_matriz(A,af,ac); llenar_matriz(A,af,ac);
  crear_matriz(B,bf,bc); llenar_matriz(B,bf,bc);

  crear_matriz(C,af,bc);
 
  clock_t start = clock();
  BlockMultiplication(A,B,C);
  printf("Tiempo transcurrido bloques : %f", ((double)clock() - start));
  printf("\n");
 // mostrar_matriz(A,af,ac);
  // mostrar_matriz(B,bf,bc);
 // mostrar_matriz(C,af,bc);
  


}
