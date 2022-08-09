#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
	int age, num;
	char name[50];

}student;

void swap(student* a, student* b)
{
    student t = *a;
    *a = *b;
    *b = t;
}

int partition(student arr[], int ini, int fim){
	int esq, dir;
	char piv[50];
	esq = ini;
	dir = fim;
	strcpy(piv, arr[ini].name);
	//piv = arr[ini].age;

	while(esq < dir){
		while(esq <= fim && (strcmp(arr[esq].name, piv) <= 0))
			esq++;
		while(dir >= 0 && (strcmp(arr[dir].name, piv) > 0))
			dir--;

		if(esq < dir){
			swap(&arr[esq], &arr[dir]);
		}
	}

	swap(&arr[ini], &arr[dir]);
	// arr[ini] = arr[dir];
	// arr[dir] = piv;
	return dir;
}
 
void quickSort(student arr[], int ini, int fim){	
	int piv;
	if(fim > ini){
		piv = partition(arr, ini, fim);
		quickSort(arr, ini, piv-1);
		quickSort(arr, piv+1, fim);
	}
}

int main(int argc, char* argv[]){
	student arrStudents[100]; 
	int len = argc-1, j = 1;

	printf("\nBefore:\n");
	for(int i = 0; i < len/3; i++){
		arrStudents[i].age = atoi(argv[j]); j++;
		arrStudents[i].num = atoi(argv[j]); j++;
		strcpy(arrStudents[i].name, argv[j]); j++;

		printf("\nStudent %d\nAge: %d, Num: %d, Name: %s\n", i+1, arrStudents[i].age, arrStudents[i].num, arrStudents[i].name);
	}

	printf("\n=====================After=======================:\n");
	quickSort(arrStudents, 0, (len/3)-1);
	for(int i = 0; i < len/3; i++){
		printf("\nStudent %d\nAge: %d, Num: %d, Name: %s\n", i+1, arrStudents[i].age, arrStudents[i].num, arrStudents[i].name);
	}
	printf("\n");

    return 0;
}