#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*
	Evitar firulas no arquivo (, |, :, [] ,...), o estilo posso aplicar dps.
*/

int N = 1000;
int canc[100][100];

int main(int argc, char* argv[]){
	FILE* arq = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	if(arq == NULL){
		printf("Error at opening file!\n");
		exit(1);
	}

	int lin, col, qntd;
	fscanf(arq, "%d %d %d", &lin, &col, &qntd);
	while(qntd--){
		int i, j;
		fscanf(arq, "%d %d", &i, &j);
		canc[i][j] = 1;
	}

	char ans[100] = { 0 };

	for(int i = 0; i < lin; i++){
		memset(ans, 0, sizeof(ans));
		for(int j = 0; j < col; j++){
			if(canc[i][j])
				strcat(ans, "0 ");
			else
				strcat(ans, "1 ");
		}
		fprintf(out, "%s\n", ans);
	}

	fclose(arq);
	fclose(out);
	return 0;
}