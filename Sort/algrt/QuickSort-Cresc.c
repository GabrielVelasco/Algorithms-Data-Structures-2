#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int ini, int fim){
	int esq, dir, piv;
	esq = ini;
	dir = fim;
	piv = arr[ini];

	while(esq < dir){
		while(esq <= fim && arr[esq] <= piv)
			esq++;
		while(dir >= 0 && arr[dir] > piv)
			dir--;

		if(esq < dir){
			swap(&arr[esq], &arr[dir]);
		}
	}

	arr[ini] = arr[dir];
	arr[dir] = piv;
	return dir;
}
 
void quickSort(int arr[], int ini, int fim){	
	int piv;
	if(fim > ini){
		piv = partition(arr, ini, fim);
		quickSort(arr, ini, piv-1);
		quickSort(arr, piv+1, fim);
	}
}

int main(int argc, char* argv[]){
	int arr[100], len = argc-1;
	printf("\nAntes:\n");
	for(int i = 1, j = 0; i <= len; i++, j++){
		arr[j] = atoi(argv[i]);
		printf("[%d] ", arr[j]);
	}
	printf("\n");
	quickSort(arr, 0, len-1);
	for(int i = 0; i < len; i++){
		printf("[%d] ", arr[i]);
	}
	printf("\n");
    return 0;
}