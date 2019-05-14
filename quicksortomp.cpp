#include<iostream>
#include<algorithm>
#include "omp.h"
using namespace std;

int n = 60000000;
int * Vet = new int [60000000];

void generate_list(int * x, int n) {
   int i,j,t;
   for (i = 0; i < n; i++)
     x[i] = i;
   for (i = 0; i < n; i++) {
     j = rand() % n;
     t = x[i];
     x[i] = x[j];
     x[j] = t;
   }
}

void quickSort(int* vet, int left, int right, int cutoff) 
{
	
	int i = left, j = right;
	int aux;
	int pivot = vet[(i + j) / 2];

	
	{
		while (i <= j) {
			while (vet[i] < pivot)
				i++;
			while (vet[j] > pivot)
				j--;
			if (i <= j) {
				aux = vet[i];
				vet[i] = vet[j];
				vet[j] = aux;
				i++;
				j--;
			}
		}

	}


	if ( ((right-left)<cutoff) ){
		if (left < j){quickSort(vet, left, j, cutoff); }			
		if (i < right){quickSort(vet, i, right, cutoff); }

	}else{
		#pragma omp task 	
		{quickSort(vet, left, j, cutoff); }
		#pragma omp task 	
		{quickSort(vet, i, right, cutoff); }		
	}

}

int main(){
	generate_list(Vet, n);
	omp_set_nested(1);

	#pragma omp parallel num_threads(2)
	{	
		#pragma omp single nowait
		{
			quickSort(Vet, 0, n-1, 1000);	
		}
	}	
   cout<<is_sorted(Vet,Vet+n);
	return(0);
}
