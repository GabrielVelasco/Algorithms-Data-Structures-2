#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*
	Evitar firulas no arquivo (, |, :, [] ,...), o estilo posso aplicar dps.
*/

int N = 1000;

int main(int argc, char* argv[]){
	FILE* arq = fopen(argv[1], "r");
	FILE* arq2 = fopen(argv[2], "w");
	if(arq == NULL || arq2 == NULL ){
		printf("Error at opening file!\n");
		exit(1);
	}

	char str[N];
	while(true){
		fgets(str, N, arq);
		if(feof(arq))
			break;
		for(int i = 0; i < strlen(str); i++){
			str[i] = toupper(str[i]);
		}

		fputs(str, arq2);
	}

	fclose(arq);
	fclose(arq2);
	return 0;
}