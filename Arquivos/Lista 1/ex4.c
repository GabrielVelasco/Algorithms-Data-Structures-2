#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
	Evitar firulas no arquivo (, |, :, [] ,...), o estilo posso aplicar dps.
*/

int main(int argc, char* argv[]){
	FILE* arq = fopen(argv[1], "r");
	if(arq == NULL){
		printf("Error at opening file!\n");
		exit(1);
	}

	int arrVog[500];
	memset(arrVog, 0, sizeof(arrVog));
	arrVog['a'] = 1;
	arrVog['e'] = 1;
	arrVog['i'] = 1;
	arrVog['o'] = 1;
	arrVog['u'] = 1;

	int N = 1000, vog = 0, con = 0;
	char str[N];
	while(true){
		fgets(str, N, arq);
		if(feof(arq))
			break;

		for(int i = 0; i < strlen(str); i++){
			if(str[i] >= 'a' && str[i] <= 'z'){
				if(arrVog[str[i]])
					vog ++;
				else
					con ++;
			}
		}
	}

	printf("Vog == %d\nCon == %d\n", vog, con);

	fclose(arq);
	return 0;
}