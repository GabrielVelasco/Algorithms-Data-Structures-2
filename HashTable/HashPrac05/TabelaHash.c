// https://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/
// http://stackoverflow.com/questions/2624192/good-hash-function-for-strings

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabelaHash.h" //inclui os Protótipos

//Definição do tipo Hash
struct hash{
    int qtd, TABLE_SIZE, TAMANHO_TIPO; // tam(bytes) do tipo do dado q hashta armazena
    Galo **itens; // array de point, p/ alocar espaco na mem tem que ter ponteiro.

};

Hash* criaHash(int TABLE_SIZE, int TAMANHO_TIPO){
    Hash* ha = (Hash*) malloc(sizeof(Hash));
    if(ha != NULL){
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->TAMANHO_TIPO = TAMANHO_TIPO;
        ha->itens = (Galo**) malloc(TABLE_SIZE * sizeof(Galo*));
        if(ha->itens == NULL){
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for(i=0; i < ha->TABLE_SIZE; i++)
            ha->itens[i] = NULL;
    }
    return ha;
}

void liberaHash(Hash* ha){
    if(ha != NULL){
        int i;
        for(i=0; i < ha->TABLE_SIZE; i++){
            if(ha->itens[i] != NULL)
                free(ha->itens[i]);
        }
        free(ha->itens);
        free(ha);
    }
}

int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

int sondagemLinear(int pos, int i, int TABLE_SIZE){
    return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}

int insereHash_EnderAberto(Hash* ha, void *al, int key){
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE)
        return 0;

    int i, pos, newPos;
    pos = chaveDivisao(key,ha->TABLE_SIZE);
    for(i=0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemLinear(pos,i,ha->TABLE_SIZE);

        if(ha->itens[newPos] == NULL){
            Galo *novo = (Galo*) malloc(sizeof(Galo));
            if(novo == NULL)
                return 0;

            novo->key = key;
            novo->item = malloc(ha->TAMANHO_TIPO); // 'reserva' qntd de bytes de acordo com a struct a ser usada (Aluno)
            memcpy(novo->item, al, ha->TAMANHO_TIPO); // copia os dados para 'pos reservada'

            ha->itens[newPos] = novo;
            ha->qtd++;
            return 1;
        }
    }

    return 0;
}

int buscaHash_EnderAberto(Hash* ha, int mat, void* al){
    if(ha == NULL)
        return 0;

    int i, pos, newPos;
    pos = chaveDivisao(mat,ha->TABLE_SIZE);
    for(i=0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemLinear(pos,i,ha->TABLE_SIZE);

        if(ha->itens[newPos] == NULL)
            return 0;

        if(ha->itens[newPos]->key == mat){
            memcpy(al, ha->itens[newPos]->item, ha->TAMANHO_TIPO);
            return 1;
        }
    }
    return 0;
}

int tamanhoHash(Hash *ha){
    return ha->qtd;
}

void reallocTable(Hash **ha, int newSize){
    Hash *newHa = criaHash(newSize, (*ha)->TAMANHO_TIPO);

    // copiar dados da tabela antiga para nova
    int tamAntigo = (*ha)->TABLE_SIZE;
    for(int i = 0; i < tamAntigo; i++){
        if((*ha)->itens[i] != NULL){
            Galo *tmp = (*ha)->itens[i];
            if(!insereHash_EnderAberto(newHa, tmp->item, tmp->key))
                exit(1);
        }
    }
    // liberaHash(*ha);
    free((*ha)->itens);
    free(*ha);

    *ha = newHa;
}