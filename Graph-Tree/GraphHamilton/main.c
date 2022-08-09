#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main(){
    int eh_digrafo = 0;
    Grafo* gr = cria_Grafo(5, 5, 1);

    insereAresta(gr, 0, 1, eh_digrafo, 2);
    insereAresta(gr, 0, 2, eh_digrafo, 3);
    insereAresta(gr, 1, 3, eh_digrafo, 3);
    insereAresta(gr, 1, 4, eh_digrafo, 3);
    // insereAresta(gr, 0, 4, eh_digrafo, 0);

    float dist[5]; 
    int ant[5];
    menorCaminho_Grafo(gr, 0, ant, dist);
    printf("%f\n", dist[4]);
    
    libera_Grafo(gr);

    return 0;
}

