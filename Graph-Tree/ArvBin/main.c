#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

int main(){
	FILE* p = fopen("alunos.txt", "r");
	if(p == NULL)
		exit(1);

	ArvAVL* Tree = cria_ArvAVL();
	student st;

	while(1){
		fscanf(p, "%d %s %d %d %d", &st.mat, st.name, &st.p1, &st.p2, &st.p3);

		insere_ArvAVL(Tree, st);

		if(feof(p))
			break;
	}

	if(consulta_ArvAVL(Tree, "Aleixa", &st)){
		printf("NOME: %s, P1: %d, P2: %d\n", st.name, st.p1, st.p2);
	}else
		printf("NAO ACHOUKKKKKKKKKKKK\n");

	printf("Altura: %d\n", altura_ArvAVL(Tree));

	fclose(p);
    return 0;
}
