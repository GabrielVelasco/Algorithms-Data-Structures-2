/*
    Made by:
        Amauri Pietropaolo Tavares Junior
        Carlos Henrique Silva de Oliveira Bueno  
        Gabriel de Araujo Velasco
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "h_table.h"

int main(){
    int TABLE_SIZE = 211;
    Hash *ht = criaHash(TABLE_SIZE, sizeof(struct aluno));
    FILE *fPointer = fopen("alunos.txt", "r");
    if(fPointer == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    struct aluno al;
    do{
        if(fscanf(fPointer, "%d %s %d %d %d", &al.matricula, al.nome, &al.n1, &al.n2, &al.n3) != EOF)
            insereHash(&ht, &al, al.matricula);
    }while(!(feof(fPointer)));

    int busca;
    printf("Digite uma matricula para busca: ");
    scanf("%d", &busca);
    if(buscaHash(ht, &al, busca)){
        printf("Aluno encontrado!\n");
        printf("Nome: %s\nMat: %d\nNota 1: %d\nNota 2: %d\nNota 3: %d\n", al.nome, al.matricula, al.n1, al.n2, al.n3);
    }
    else printf("Aluno nao encontrado!\n");

    liberaHash(ht);
    ht = NULL;



    fclose(fPointer);
    return 0;
}