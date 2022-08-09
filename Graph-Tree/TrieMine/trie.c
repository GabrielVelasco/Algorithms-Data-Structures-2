#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

struct trieNode{
    int ehFDP; // flag pra verificar se é fim de uma palavra ou não
    Trie character[TAM_ALFABETO]; // vetor de nós de Trie, dinamicamente alocado!!!
};


Trie* criaTrie(){ 
    // aloco um ponteiro para um novo nó, inicializo ele como não sendo fim de uma palavra e preencho cada um dos campos que representam os caracteres com NULL
    Trie* no = (Trie*) malloc(sizeof(Trie)); // aloca espaco p/ pont de struct trieNode
    *no = (Trie) malloc(sizeof(struct trieNode));
    if(no != NULL){
        (*no)->ehFDP = 0;
        for(int i = 0; i < TAM_ALFABETO; i++)
            (*no)->character[i] = NULL;
    }

    return no; // retorna pont para pont
}

int insereTrie(Trie* tr, char *str){
    if(tr == NULL)
        return 0;

    Trie noAtual = *tr;
    for(int i = 0; i < strlen(str); i++){
        int indice = str[i] - 'a'; // pego a posição no alfabeto do caractere atual a ser inserido

        if(noAtual->character[indice] == NULL){ // se esse caractere já estiver inserido, ou seja, o prefixo da palavra até esse ponto existir eu não entro aqui
            // se não foi inserido, eu entro para criar esse novo caractere
            // aloca, instancia e atribui a Tree
            Trie newNode = (Trie) malloc(sizeof(struct trieNode));
            newNode->ehFDP = 0; // nao eh ultimo charac
            for(int j = 0; j < TAM_ALFABETO; j++)
                newNode->character[j] = NULL;
            noAtual->character[indice] = newNode;
        }

        // aqui eu avanço o noAtual pra continuar alocando novas árvores para cada caractere inserido
        noAtual = noAtual->character[indice];
    }

    noAtual->ehFDP = 1; // node marca o fim da palavra

    return 1;
}

int validaPalavra(char *str){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] < 'a' || str[i] >= 'a' + TAM_ALFABETO)
            return 0;
    }

    return 1;
}


int buscaTrie(Trie* tr, char *str){
    if(tr == NULL || !validaPalavra(str))
        return 0;

    Trie noAtual = *tr;
    for(int i = 0; i < strlen(str); i++){
        int indice = str[i] - 'a';
        noAtual = noAtual->character[indice];

        // se eu cheguei no fim de um caminho da Trie antes de chegar no fim da string passada
        // essa string não existe na Trie
        if(noAtual == NULL)
            return 0;
    }

    return noAtual->ehFDP;
}

int arvoreComFilhos(Trie* tr){
    // se o ponteiro pra essa árvore é nulo, não tem como o nó ter filhos
    if(tr == NULL)
        return 0;

    for(int i = 0; i < TAM_ALFABETO; i++){
        if((*tr)->character[i] != NULL) // achou qualquer ponteiro apontando pra algo retorna true
            return 1;
    }

    return 0;
}

int removeAux(Trie* tr, char *str, int i){
    if((*tr == NULL) || (!(*tr)->ehFDP && i == strlen(str))){
        return 0; // nao existe
    }

    if((*tr)->ehFDP && i == strlen(str)){ // achei a palavra
        (*tr)->ehFDP = 0;
        for(int i = 0; i < TAM_ALFABETO; i++){
            if((*tr)->character[i] != NULL) // faz parte de outra palavra, n da free em tr
                return 1;
        }
        free((*tr));
        *tr = NULL;

        return 1;
    }

    int idx = str[i] - 'a';
    int tmp = removeAux(&((*tr)->character[idx]), str, i+1);

    if(!tmp) return 0;

    if(!(*tr)->ehFDP){
        for(int i = 0; i < TAM_ALFABETO; i++){
            if((*tr)->character[i] != NULL)
                return 1;
        }

        free((*tr)); // Node n tem filhos, deleta node
        *tr = NULL;
    }

    return 1; // node faz parte de outra palavra
}

int removeTrie(Trie* tr, char *str){
    if(tr == NULL || !validaPalavra(str))
        return 0;
    
    return removeAux(tr, str, 0);
}

void imprimeAux(Trie* tr, char *str, int pos){
    if(*tr == NULL)
        return;

    if((*tr)->ehFDP){
        for(int i = 0; i < pos; i++)
            printf("%c", str[i]);

        printf("\n");
    }
    for(int i = 0; i < TAM_ALFABETO; i++){
        if((*tr)->character[i] != NULL){
            str[pos] = i + 'a';
            imprimeAux(&((*tr)->character[i]), str, pos+1); // nova raiz...
        }
    }
}

void imprimeTrie(Trie* tr){
    char str[26] = "";
    imprimeAux(tr, str, 0);

}

void autocompletarTrie(Trie* tr, char *prefixo){
    int i = 0;
    while(1){
        if(strlen(prefixo) == i){
            char str[26]= "";
            autocompletarAux(tr, str, 0, prefixo);
            return;
        }
        if((*tr)->character[prefixo[i] - 'a'] == NULL){
            return;
        }
        tr = &((*tr)->character[prefixo[i] - 'a']);
        i++;
    }
}

void autocompletarAux(Trie* tr, char *str, int pos, char* prefixo){
    if(*tr == NULL)
        return;

    if((*tr)->ehFDP){
        printf("%s", prefixo);
        for(int i = 0; i < pos; i++)
            printf("%c", str[i]);

        printf("\n");
    }
    for(int i = 0; i < TAM_ALFABETO; i++){
        if((*tr)->character[i] != NULL){
            str[pos] = i + 'a';
            autocompletarAux(&((*tr)->character[i]), str, pos+1, prefixo);
        }
    }
}
