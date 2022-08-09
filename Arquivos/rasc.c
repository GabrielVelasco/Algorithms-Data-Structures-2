#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char* argv[]){
	FILE* arq = fopen(argv[1], "w");

	int n;
	printf("Quantos estudantes? ");
	scanf("%d", &n);
	char nome[50];
	int matr, nota, i = 1;
	while(n--){
		printf("\nAluno %d:\n", i);
		printf("Matricula (inteiro): ");
		scanf("%d", &matr);
		printf("Nome: ");
		scanf(" %[^\n]", nome);
		printf("Nota: ");
		scanf("%d", &nota);
		fprintf(arq, "Aluno %d: %d %s %d\n", i, matr, nome, nota);
		i++;
	}

	fclose(arq);
	return 0;
}