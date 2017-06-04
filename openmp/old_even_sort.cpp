#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
using namespace std;

void first_odd_even(int *a, int n, int Nthreads)
{
	int phase,i,tmp;
	for (phase = 0; phase < n; phase++)
	{
		if (phase % 2 == 0)
#			pragma omp parallel for num_threads(Nthreads) \
				default(none) shared(a, n) private(i, tmp)
			for (i = 1; i < n; i += 2)
			{
				if (a[i - 1] > a[i])
				{
					tmp = a[i - 1];
					a[i - 1] = a[i];
					a[i] = tmp;
				}
			}
		else
#			pragma omp parallel for num_threads(Nthreads) \
				default(none) shared(a, n) private(i, tmp)
			for (i = 1; i < n - 1; i += 2)
			{
				if (a[i] > a[i+1])
				{
					tmp = a[i+1];
					a[i+1] = a[i];
					a[i] = tmp;
				}
			}
	}
}

void second_odd_even(int *a, int n, int Nthreads)
{
	int phase,i,tmp;
#	pragma omp parallel num_threads(Nthreads) \
		default(none) shared(a, n) private(i, tmp, phase)
	for (phase = 0; phase < n; phase++)
	{
		if (phase % 2 == 0)
#			pragma omp for
			for (i = 1; i < n; i += 2)
			{
				if (a[i - 1] > a[i])
				{
					tmp = a[i - 1];
					a[i - 1] = a[i];
					a[i] = tmp;
				}
			}
		else
#			pragma omp for
			for (i = 1; i < n - 1; i += 2)
			{
				if (a[i] > a[i+1])
				{
					tmp = a[i+1];
					a[i+1] = a[i];
					a[i] = tmp;
				}
			}
	}
}

void print_my_vector(int *a,int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout<a[i]<<" ";
	}
	cout<<endl;
}

int main(int argc, char const *argv[])
{
	int Nthreads=5;
	int n=200000;
	int *my_vector=new int[n];


	/* initialize random seed: */
  	srand (time(NULL));
	for (int i = 0; i < n; ++i){my_vector[i]=rand() % 100;}


	//print_my_vector(my_vector,n);
	auto start = chrono::high_resolution_clock::now();
	first_odd_even(my_vector,n,Nthreads);
	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "Primera implementacion: " << elapsed.count() <<endl;
	//print_my_vector(my_vector,n);



	auto start2 = chrono::high_resolution_clock::now();
	second_odd_even(my_vector,n,Nthreads);
	auto finish2 = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed2 = finish2 - start2;
	cout << "Segunda implementacion: " << elapsed2.count() <<endl;
	//print_my_vector(my_vector,n);
	return 0;
}
