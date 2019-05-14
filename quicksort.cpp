#include<iostream>
#include<algorithm>
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

void quickSort(int* vet, int left, int right) 
{
	
	int i = left, j = right;
	int aux;
	int pivot = array[(i + j) / 2];

	
	{
		while (i <= j) {
			while (array[i] < pivot)
				i++;
			while (array[j] > pivot)
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
	if (left < j){ quickSort(vet, left, j); }			
	if (i < right){ quickSort(vet, i, right); }
}


int main(){
	generate_list(Vet, n);
 	quickSort(Vet, 0, n);
    cout<<is_sorted(Vet,Vet+n);
	return(0);
}
