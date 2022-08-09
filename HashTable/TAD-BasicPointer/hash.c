#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

struct hash{
	int TABLE_SIZE, qty;
	struct aluno **arr;

};

Hash* createHash(int MAXS){
	Hash* ha = (Hash*)malloc(sizeof(Hash));
	if(ha != NULL){
		ha->TABLE_SIZE = MAXS;
		ha->arr = (struct aluno**)malloc(MAXS * sizeof(struct aluno*));
		if(ha->arr == NULL){
			free(ha);
			return NULL;
		}
		ha->qty = 0;
		for(int i = 0; i < MAXS; i++)
			ha->arr[i] = NULL;
	}

	return ha;
}

int linearProbing(int index, int i, int TABLE_SIZE){
	return ((index + i) & 0x7FFFFFFF) % TABLE_SIZE;
}

int chaveDiv(int chave, int TABLE_SIZE){
	return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

int insertHash(Hash* ha, struct aluno al){
	if(ha == NULL || ha->qty == ha->TABLE_SIZE)
		return 0;

	int chave = al.matricula;
	int pos = chaveDiv(chave, ha->TABLE_SIZE), newPos;

	for(int i = 0; i < ha->TABLE_SIZE; i++){
		newPos = linearProbing(pos, i, ha->TABLE_SIZE);
		if(ha->arr[newPos] == NULL){
			struct aluno *newAL;
			newAL = (Aluno*)malloc(sizeof(Aluno));
			if(newAL == NULL)
				return 0;

			*newAL = al;
			ha->arr[newPos] = newAL;
			ha->qty ++;

			return 1;
		}
	}

	return 0;
}

int buscaHash(Hash* ha, int key, Aluno *alRetorno){
	if(ha == NULL)
		return 0;

	int pos = chaveDiv(key, ha->TABLE_SIZE), newPos;

	for(int i = 0; i < ha->TABLE_SIZE; i++){
		newPos = linearProbing(pos, i, ha->TABLE_SIZE);
		if(ha->arr[newPos] == NULL)
			return 0; // nao existe
		
		if(ha->arr[newPos]->matricula == key){
			*alRetorno = *(ha->arr[newPos]); // retorno impirico
			return 1;
		}
	}

	return 0;
}

void clearHash(Hash *ha){
	if(ha != NULL){
		for(int i = 0; i < ha->TABLE_SIZE; i++){
			if(ha->arr[i] != NULL)
				free(ha->arr[i]);
			
		}
		free(ha->arr);
		free(ha);
	}
}

void printHash(Hash *ha){
	printf("\nHash Table:\n");
	for(int i = 0; i < ha->TABLE_SIZE; i++){
		if(ha->arr[i] != NULL){
			printf("Nome: %s, Mat: %d\n", ha->arr[i]->nome, ha->arr[i]->matricula);
		}
	}
}