#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TabelaHash.h"

int main(){
	int tableSize = 10;
	Hash *ha = criaHash(tableSize, sizeof(Aluno));
	FILE *pFile = fopen("alunos.txt", "r");
	if(pFile == NULL){
		printf("Errror at opening the file\n");
		exit(1);
	}

	char nome[50] = { 0 };
	int p1, p2, p3, mat;
	Aluno al;

	while(1){
		// le linha por linha do arquivo 
		fscanf(pFile, "%d %s %d %d %d", &al.matricula, al.nome, &al.n1, &al.n2, &al.n3);
		if(feof(pFile))
			break;

		insereHash_EnderAberto(ha, &al, al.matricula);	
		if(tamanhoHash(ha) >= ((float)0.75*tableSize)){
			// realloc e dobra tableSize
			tableSize *= 2;
			reallocTable(&ha, tableSize);
		}
	}

	int buscaMat;
	printf("\nDigite uma matricula para busca: ");
	scanf("%d", &buscaMat);
	if(buscaHash_EnderAberto(ha, buscaMat, &al)){
		printf("\nRetorno:\n");
		printf("Nome: %s, Mat: %d, P1: %d, P2: %d, P3: %d\n", al.nome, al.matricula, al.n1, al.n2, al.n3);
	}else{
		printf("\nMatricula nao encontrada!\n");
	}
	
	printf("\nLiberando Hash!\n");
	liberaHash(ha);
	ha = NULL;

    fclose(pFile);
    return 0;
}