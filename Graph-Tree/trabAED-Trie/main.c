#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

/*
    Amauri Pietropaolo Tavares Junior - 11921BCC007
    Carlos Henrique Silva de Oliveira Bueno - 11911BCC005
    Gabriel de Araujo Velasco - 11921BCC003
    Gabriella Marçal Silva - 11321GIN005
*/

int main(){
    Trie *tr = criaTrie();
    FILE *fPointer = fopen("palavras.txt", "r");
    if(fPointer == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    printf("Debug de printf numero 1. Tentativa de inserir\n");
    char str[26];
    do{
        if(fscanf(fPointer, "%s", str))
            insereTrie(tr, str);
    }while(!(feof(fPointer)));

    // printf("Remove concernente - %d\n", removeTrie(tr, "concernente"));
    // printf("Busca concerne - %d\n", buscaTrie(tr, "concerne"));
    // printf("Busca concernente - %d\n", buscaTrie(tr, "concernente"));


    printf("Debug de printf numero 2. Tentativa de busca de abnegado\n");
    printf("%d\n", buscaTrie(tr, "abnegado"));
    printf("Debug de printf numero 3. Tentativa de busca de bilateral\n");
    printf("%d\n", buscaTrie(tr, "bilateral"));
    printf("Debug de printf numero 4. Tentativa de busca de zorro\n");
    printf("%d\n", buscaTrie(tr, "zorro"));
    printf("Debug de printf numero 5. Tentativa de busca de concerne\n");
    printf("%d\n", buscaTrie(tr, "concerne"));
    printf("Debug de printf numero 6. Tentativa de busca de consiste\n");
    printf("%d\n", buscaTrie(tr, "consiste"));
    printf("Debug de printf numero 7. Tentativa de busca de conserto\n");
    printf("%d\n", buscaTrie(tr, "conserto"));
    printf("Debug de printf numero 8. Tentativa de busca de conceito\n");
    printf("%d\n", buscaTrie(tr, "conceito"));
    printf("Debug de printf numero 9. Tentativa esperando falha. Buscando zzzzz\n");
    printf("%d\n", buscaTrie(tr, "zzzzz"));

    printf("Debug de printf numero 10. Tentativa de remocao de concerne\n");
    printf("%d\n", removeTrie(tr, "concerne"));
    // O retorno é 0 mesmo a remocao aparentemente dando certo
    printf("Debug de printf numero 11. Tentativa de busca de concerne apos remocao\n");
    printf("%d\n", buscaTrie(tr, "concerne"));
    // Não achei depois de remover, então acho que deu certo
    printf("Debug de printf numero 12. Tentativa de busca de concernente apos remocao de concerne (prefixo)\n");
    printf("%d\n", buscaTrie(tr, "concernente")); // Isso aqui funciona aparentemente, mas não tem como saber até o retorno da remoção dar certo

    printf("Tentando remover algo que não existe\n");
    printf("%d\n", removeTrie(tr, "mundialdopalmeiras"));

    //imprimeTrie(tr);
    //printf("\nPre autocomplete\n\n");
    //autocompletarTrie(tr, "con");
    //printf("\nPos autocomplete\n\n");
    //imprimeTrie(tr);

    printf("\nautocomplete com prefix = 'xo':\n");
    autocompletarTrie(tr, "xo");

    liberaTrie(tr);
    imprimeTrie(tr);

    return 0;
}