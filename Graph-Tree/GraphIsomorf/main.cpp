#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include <string>
#include <bits/stdc++.h>

using namespace std;

int stringHash(string s){
    int index = 0;
    for(int i = 0; i < s.size(); i++)
        index = (3*index + (int)s[i]) % 50;

    return index;
}

int main(){
    int eh_digrafo = 1;
    Grafo* gr = cria_Grafo(50, 50, 0);

    // le arq.txt linha/linha, cada linha separa string por espaco, salva cada termo em um vector<string>
    // criaAresta(vec[i-1], vec[i], ...)
    // repte. ...

    FILE *p = fopen("arq.txt", "r");
    if(p == NULL)
        exit(1);

    char str[50] = { 0 };
    while(1){
        v.clear();
        fgets(str, 50, p);
        if(feof(p))
            break;
        
        istringstream ss (str);
        string t; ss >> t; int prim = stringHash(t);
        while(ss >> t){
            insereAresta(gr, prim, t, eh_digrafo, 1);
        }
    }

    // imprime_Grafo(gr);
    // printf("\n");
    libera_Grafo(gr);
    fclose(p);
    return 0;
}
