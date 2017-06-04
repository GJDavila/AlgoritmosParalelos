#include<stdio.h>
#include<iostream>
|using namespace std;

///compilar
////usr/local/cuda/bin/nvcc summatriz.cu -o sum


///funciones kernels

 __global__ void  MatrizAddKernel_B(float *A, float *B, float* C, int n)
 {
                 int i=threadIdx.x + blockDim.x * blockIdx.x;
                  if(i<(n*n)) C[i]=A[i]+B[i];
 }

 __global__ void MatrizAddKernel_C(float *A, float* B, float* C, int n)
 {
 		int i=n*blockIdx.x;
 		for(int j=0;j<n;j++)
 		{
 			C[i+j]=A[i+j]+B[i+j];
 		}
 }

 __global__ void  MatrizAddKernel_D(float *A, float* B, float* C, int n)
 {
 		int i=blockIdx.x;
 		for(int j=0;j<n;j++)
 		{
 			C[i+n*j]=A[i+n*j]+B[i+n*j];
 		}
 }
 void MatrizAdd(float *A, float* B, float* C, int n)
 {
         int size = n*n * sizeof(float);
         float *d_A, *d_B, *d_C;
         cudaMalloc((void **) &d_A, size);
         cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
         cudaMalloc((void **) &d_B, size);
         cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);
         cudaMalloc((void **) &d_C, size);
         MatrizAddKernel_B<<<5,20>>>(d_A, d_B, d_C, n);
         //MatrizAddKernel_C<<<n,1>>>(d_A, d_B, d_C, n);
         //MatrizAddKernel_D<<<n,1>>>(d_A, d_B, d_C, n);
         cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
         // Free device memory for A, B, C
         cudaFree(d_A); cudaFree(d_B); cudaFree (d_C);
 }
 int main()
 {
   float *A,*B,*C;
   int n=10;
   A=new float[n*n];
   B=new float[n*n];
   C=new float[n*n];
   for(int i=0;i<n*n;i++){A[i]=i;B[i]=i;}

   MatrizAdd(A,B,C,n);
   for(int i=0;i<n*n;i++)
   {
     cout<<C[i]<<" ";
   }

 }
