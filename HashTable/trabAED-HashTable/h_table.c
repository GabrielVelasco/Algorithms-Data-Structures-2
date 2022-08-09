#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "h_table.h"


struct hash{
    int qt, TABLE_SIZE, TYPE_SIZE;
    Item **items;
};

// Única mudança nesse caso é que agora eu guardo o tamanho dos dados que eu vou guardar na tabela
Hash* criaHash(int TABLE_SIZE, int TYPE_SIZE){
    Hash* ht = (Hash*) malloc(sizeof(Hash));
    if(ht != NULL){
        int i;
        ht->TABLE_SIZE = TABLE_SIZE;
        ht->TYPE_SIZE = TYPE_SIZE;
        ht->items = (Item **) malloc(TABLE_SIZE*sizeof(Item*));
        if(ht->items == NULL){
            free(ht);
            return NULL;
        }
        ht->qt = 0;
        for(i = 0; i < ht->TABLE_SIZE; i++)
            ht->items[i] = NULL;
    }
    return ht;
}

void liberaHash(Hash* ht){
    if(ht != NULL){
        int i;
        for(i = 0; i < ht->TABLE_SIZE; i++){
            if(ht->items[i] != NULL)
                free(ht->items[i]);
        }
        free(ht->items);
        free(ht);
    }
}

int divKey(int key, int TABLE_SIZE){
    return (key & 0x7FFFFFFF) % TABLE_SIZE;
}

int quadProbe(int pos, int i, int TABLE_SIZE){
    pos = pos + 2*i + 5*i*i;
    return (pos & 0x7FFFFFFF) % TABLE_SIZE;
}

int resizeTable(Hash **ht){
    // Crio uma nova hash com o dobro do tamanho da tabela inicial
    Hash* newHT = criaHash(2*(*ht)->TABLE_SIZE, (*ht)->TYPE_SIZE);
    if(newHT == NULL)
        return 0;

    // Inserção de todos os itens da tabela antiga na tabela nova
    for(int i = 0; i < (*ht)->TABLE_SIZE; i++){
        if((*ht)->items[i] != NULL){
            // Se a inserção deu errado retorna 0
            // Não há liberação da antiga tabela e os dados são preservados
            if(!(insereHash(&newHT, (*ht)->items[i]->genericData, (*ht)->items[i]->key)))
                return 0;
        }
    }

    // Libera a antiga tabela
    liberaHash(*ht);
    // Associa o endereço da antiga tabela à nova
    *ht = newHT;

    return 1;
}

// Passo ht por referencia para o caso de precisar alterar (na função de resize)
int insereHash(Hash **ht, void* genericData, int key){
    if(*ht == NULL)
        return 0;
    // Verifica se a tabela está 75% cheia
    // Se estiver, chama a função de resize
    if((*ht)->qt >= 0.75*(*ht)->TABLE_SIZE){
        int ret = resizeTable(ht);
        // Se falhar em dar resize retorna 0 e não insere
        if(ret == 0)
            return 0;
    }

    // Tendo que dar resize ou não, insere na tabela
    int pos = divKey(key, (*ht)->TABLE_SIZE); // Gera uma posição a partir da chave
    for(int i = 0; i < (*ht)->TABLE_SIZE; i++){
        // Tratamento de colisão
        int newPos = quadProbe(pos, i, (*ht)->TABLE_SIZE);
        if((*ht)->items[newPos] == NULL){
            // Aloca o novo item a ser colocado na tabela. Se falhar retorna 0
            Item *newItem = (Item *) malloc(sizeof(Item));
            if(newItem == NULL)
                return 0;

            // Guarda a chave desse novo item para busca e os dados 
            newItem->key = key;
            newItem->genericData = malloc((*ht)->TYPE_SIZE);
            // memcpy para conseguir guardar o valor no ponteiro void
            memcpy(newItem->genericData, genericData, (*ht)->TYPE_SIZE); 

            (*ht)->items[newPos] = newItem; // Associa o novo item à posição dele na tabela
            (*ht)->qt++; // Atualiza a quantidade de itens na tabela

            return 1;
        }
    }

    return 0;
}

int buscaHash(Hash* ht, void* genericData, int key){
    if(ht == NULL)
        return 0;
    
    // Pego uma posição que a key pode estar e depois faço tratamento de colisão
    int pos = divKey(key, ht->TABLE_SIZE), newPos;
    for(int i = 0; ht->TABLE_SIZE; i++){
        newPos = quadProbe(pos, i, ht->TABLE_SIZE);
        // Não achou retorna 0
        if(ht->items[newPos] == NULL)
            return 0;

        if(ht->items[newPos]->key == key){
            // memcpy para conseguir guardar o valor no ponteiro void
            // Esse ponteiro void na main vai ser uma variável do tipo de dado guardado na tabela passada por referência
            memcpy(genericData, ht->items[newPos]->genericData, ht->TYPE_SIZE);
            return 1;
        }
    }
}