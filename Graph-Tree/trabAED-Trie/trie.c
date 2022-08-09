#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

struct trieNode{
    int ehFDP; // flag pra verificar se � fim de uma palavra ou n�o
    Trie character[TAM_ALFABETO]; // vetor de n�s de Trie
};


Trie* criaTrie(){ // aloco um ponteiro para um novo n�, inicializo ele como n�o sendo fim de uma palavra e preencho cada um dos campos que representam os caracteres com NULL
    Trie* no = (Trie*) malloc(sizeof(Trie));
    *no = (Trie) malloc(sizeof(struct trieNode));
    if(no != NULL){
     (*no)->ehFDP = 0;
        for(int i = 0; i < TAM_ALFABETO; i++)
         (*no)->character[i] = NULL;
    }

    return no;
}

int insereTrie(Trie* tr, char *str){
    if(tr == NULL)
        return 0;

    Trie noAtual = *tr;
    for(int i = 0; i < strlen(str); i++){
        int indice = str[i] - 'a'; // pego a posi��o no alfabeto do caractere atual a ser inserido
        if(noAtual->character[indice] == NULL){ // se esse caractere j� estiver inserido, ou seja, o prefixo da palavra at� esse ponto existir eu n�o entro aqui
            // se n�o foi inserido, eu entro para criar esse novo caractere
            noAtual->character[indice] = (Trie) malloc(sizeof(struct trieNode));
            noAtual->character[indice]->ehFDP = 0;
            for(int j = 0; j < TAM_ALFABETO; j++)
                noAtual->character[indice]->character[j] = NULL;
        }

        // aqui eu avan�o o noAtual pra continuar alocando novas �rvores para cada caractere inserido
        noAtual = noAtual->character[indice];
    }

    // eu marco o n� a frente como fim da palavra
    noAtual->ehFDP = 1;
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
        // essa string n�o existe na Trie
        if(noAtual == NULL)
            return 0;
    }

    return noAtual->ehFDP;
}

int arvoreComFilhos(Trie* tr){
    // se o ponteiro pra essa �rvore � nulo, n�o tem como o n� ter filhos
    if(tr == NULL)
        return 0;

    for(int i = 0; i < TAM_ALFABETO; i++){
        if((*tr)->character[i] != NULL) // achou qualquer ponteiro apontando pra algo retorna true
            return 1;
    }

    return 0;
}

/*int removeTrie(Trie* tr, char *str){
    ERRO??
    if(tr == NULL || !validaPalavra(str))
        return 0;
    // enquanto nao tiver chegado ao fim da string faz a consulta
    if(strlen(str) > 0){
        int indice = str[0] - 'a';
        if(tr != NULL && (*tr)->character[indice] != NULL && removeTrie(&(*tr)->character[indice], str + 1) && (*tr)->ehFDP == 0){
            if(!arvoreComFilhos(tr)){
                free(*tr);
                tr = NULL;
                return 1;
            }
            else return 0;
        }
    }
    else if((*tr)->ehFDP){
        if(!arvoreComFilhos(tr)){
            free(*tr);
            tr = NULL;
            return 1;
        }
        else{
            (*tr)->ehFDP = 0;
            return 0;
        }
    }

    return 0;
}*/

int removeAux(Trie* tr, char *str, int i){
    if((*tr == NULL) || (!(*tr)->ehFDP && i == strlen(str))){
        return 0; // nao existe
    }

    if((*tr)->ehFDP && i == strlen(str)){ // achei a palavra
        (*tr)->ehFDP = 0; // node n eh mais fim de palavra
        for(int i = 0; i < TAM_ALFABETO; i++){
            if((*tr)->character[i] != NULL) // faz parte de outra palavra, n da free no node, ele continua na tree.
                return 1;
        }
        free((*tr));
        *tr = NULL;

        return 1;
    }

    int idx = str[i] - 'a';
    int tmp = removeAux(&((*tr)->character[idx]), str, i+1);

    if(!tmp) return 0; // nao existe, volta recursao

    if(!(*tr)->ehFDP){ // node n eh fim de palavra, talvez eu precise deleta-lo
        for(int i = 0; i < TAM_ALFABETO; i++){
            if((*tr)->character[i] != NULL) // verif se node tem filhos
                return 1; // sim? node continua na tree
        }

        free((*tr)); // Node n tem filhos, deleta node
        *tr = NULL;
    }

    return 1; // volta recursao
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
            imprimeAux(&((*tr)->character[i]), str, pos+1);
        }
    }
}

void imprimeTrie(Trie* tr){
    char str[26] = "";
    imprimeAux(tr, str, 0);

}

void autocompletarAux(Trie* tr, char *str, int pos, char* prefixo){
    if(*tr == NULL || tr == NULL)
        return;

    // chegou no fim de uma palavra com esse prefixo, imprime ele e depois os caracteres que vieram depois dele e tão guardados em str
    if((*tr)->ehFDP){
        printf("%s", prefixo);
        for(int i = 0; i < pos; i++)
            printf("%c", str[i]);

        printf("\n");
    }
    // vai chamando recursivamente onde quer que existam caracteres depois daquele prefixo
    // os caracteres achados a cada chamada são guardados em str
    for(int i = 0; i < TAM_ALFABETO; i++){
        if((*tr)->character[i] != NULL){
            str[pos] = i + 'a';
            autocompletarAux(&((*tr)->character[i]), str, pos+1, prefixo);
        }
    }
}

void autocompletarTrie(Trie* tr, char *prefixo){
    int i = 0;
    while(1){
        // se eu avancei na árvore até chegar no fim do prefixo eu chamo a função auxiliar responsável pelo autocomplete
        if(strlen(prefixo) == i){
            char str[26]= "";
            autocompletarAux(tr, str, 0, prefixo);
            return;
        }
        // if que verifica se o prefixo está na árvore, olhando caractere a caractere nas subárvores
        if((*tr)->character[prefixo[i] - 'a'] == NULL){
            return;
        }
        // avança a árvore pra quando começar a autocompletar não ter que refazer o percorrimento desde o início dela, mas sim do último caractere do prefixo
        tr = &((*tr)->character[prefixo[i] - 'a']);
        i++;
    }
}

void liberaTrie(Trie* tr){
    if(tr == NULL || *tr == NULL)
        return;
    
    for(int i = 0; i < 26; i++){
        liberaTrie(&((*tr)->character[i]));
    }

    free(*tr);
    *tr = NULL;
}