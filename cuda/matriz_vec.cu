#include<stdio.h>
#include<iostream>
 using namespace std;

 ///compilar
 ////usr/local/cuda/bin/nvcc matriz_vec.cu -o multi



///-----------funcion kernel
__global__ void MatrizVectorKernel(float *A, float* B, float* C, int n)
{
		int i=n*blockIdx.x;
    int tmp=0;
		for(int j=0;j<n;j++)
		{
		    tmp+= (A[i+j]*B[j]);
		}
    	C[blockIdx.x] =tmp;
}

void MatrizVector(float *A, float* B, float* C, int n)
{
        int size1 = n*n * sizeof(float);
				int size2 = n * sizeof(float);
        float *d_A, *d_B, *d_C;
        cudaMalloc((void **) &d_A, size1);
        cudaMemcpy(d_A, A, size1, cudaMemcpyHostToDevice);
        cudaMalloc((void **) &d_B, size2);
        cudaMemcpy(d_B, B, size2, cudaMemcpyHostToDevice);
        cudaMalloc((void **) &d_C, size2);
        MatrizVectorKernel<<<n,1>>>(d_A, d_B, d_C, n);
        cudaMemcpy(C, d_C, size2, cudaMemcpyDeviceToHost);
        // Free device memory for A, B, C
        cudaFree(d_A); cudaFree(d_B); cudaFree (d_C);
}


int main()
{
	float *A,*B,*C;
	int n=10;
	A=new float[n*n];
	B=new float[n];
	C=new float[n];
	for(int i=0;i<n*n;i++){A[i]=i;if(i<n){B[i]=i;}}

	MatrizVector(A,B,C,n);
	for(int i=0;i<n;i++)
	{
		cout<<C[i]<<" ";
	}

}
