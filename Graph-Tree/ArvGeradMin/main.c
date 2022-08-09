#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Grafo.h"

int main(){
    int eh_digrafo = 0;
    Grafo* gr = cria_Grafo(20, 20, 1);

    srand(time(NULL));
    int aa = 16;
    for(int i = 1; i < aa; i++){
        int r = rand() % 5; r++;
        if(i != 4 && i != 8 && i != 12 && i != 16)
            insereAresta(gr, i, i+1, eh_digrafo, r);
        insereAresta(gr, i, i+4, eh_digrafo, r);
    }
    
    int pai[20];
    arvoreGeradoraMinimaKruskal_Grafo(gr, 1, pai);

    for(int i = 1; i <= 17; i++){
        printf("%d ---- %d\n", i, pai[i]);
    }

    libera_Grafo(gr);

    return 0;
}
