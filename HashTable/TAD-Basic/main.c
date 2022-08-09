#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

int main(){
	// clock_t ttt = clock();

	Hash *ha = createHash(100);

	char name[50] = { 0 };
	int mat;

	while(scanf(" %[^\n]", name) != EOF){
		// printf("YES! %s\n", name);
		
		scanf("%d", &mat);

		Aluno al;
		strcpy(al.nome, name);
		al.matricula = mat;

		insertHash(ha, al);
	}

	printHash(ha);
	
	clearHash(ha);
	printHash(ha);
    // ttt = clock() - ttt;
    // printf("Time elapsed: %f\n", (float)ttt/CLOCKS_PER_SEC);
    return 0;
}