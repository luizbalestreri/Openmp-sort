#include<iostream>
#include<fstream>
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

void merge(int aux[], int left, int middle, int right){
	int * temp = new int [middle-left+1];
	int * temp2 = new int[right-middle];
	for(int i=0; i<(middle-left+1); i++){
		temp[i]=aux[left+i];
	}
	for(int i=0; i<(right-middle); i++){
		temp2[i]=aux[middle+1+i];
	}
	int i=0, j=0, k=left;
	while(i<(middle-left+1) && j<(right-middle))
	{
		if(temp[i]<temp2[j]){
			aux[k++]=temp[i++];
		}
		else{
			aux[k++]=temp2[j++];
		}
	}
	while(i<(middle-left+1)){
		aux[k++]=temp[i++];
	}
	while(j<(right-middle)){
		aux[k++]=temp2[j++];
	}
}

void mergeSortSerial(int aux[], int left, int right){
	if (left < right){
		int middle = (left + right)/2;
		mergeSortSerial(aux,left,middle); //call 1
		mergeSortSerial(aux,middle+1,right); //call 2
		merge(aux,left,middle,right);
	}
}

void mergeSort (int aux[], int left, int right){
	if (left < right){
		if ((right-left) > 100000){
			int middle = (left + right)/2;
		   #pragma omp task firstprivate (aux, left, middle)
				mergeSort(aux,left,middle); //call 1
			#pragma omp task firstprivate (aux, middle, right)
				mergeSort(aux,middle+1,right); //call 2
			#pragma omp taskwait
			merge(aux,left,middle,right);
		} else{mergeSortSerial(aux, left, right);}
	}
}

void print(int aux[], int n)
{
	for(int i=0; i<n; i++)
		cout<<aux[i]<<" ";
	cout<<endl;
}



int main(){
	generate_list(Vet, n);
	omp_set_nested(1);
	omp_set_num_threads(2);

	   #pragma omp parallel
   {
      #pragma omp single
 		mergeSort(Vet, 0, n-1);
   }

	return(0);
}