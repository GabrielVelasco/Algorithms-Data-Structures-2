#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0
#define MAXS 10503

/*
    char str[30] = { 0 }; initialize str with length 0
*/

typedef struct tree{
    char name[35];
    float val;

}Tree;

typedef struct hash{
	int TABLE_SIZE, qty;
	struct tree **arr;

}Hash;

char treeName[35] = { 0 }, buf;
Tree arrTree[MAXS];

Hash* createHash(){
	Hash* ha = (Hash*)malloc(sizeof(Hash));
	if(ha != NULL){
		ha->TABLE_SIZE = MAXS;
		ha->arr = (struct tree**)malloc(MAXS*sizeof(struct tree*));
		if(ha->arr == NULL){
			free(ha);
			return NULL;
		}
		ha->qty = 0;
		for(int i = 0; i < MAXS; i++)
			ha->arr[i] = NULL;
	}

	return ha;
}

int stringHash(){
	int len = strlen(treeName), index = 0;
	for(int i = 0; i < len; i++)
		index = (3*index + (int)treeName[i]) % MAXS;

	return index;
}

int linearProbing(int index, int i){
	return ((index + i) & 0x7FFFFFFF) % MAXS;
}

int insertHash(Hash* ha){
	if(ha == NULL || ha->qty == ha->TABLE_SIZE)
		return 0;

	// key == string treeName
	int index = stringHash(), newIndex;
	for(int i = 0; i < MAXS; i++){
		newIndex = linearProbing(index, i);
		if(ha->arr[newIndex] == NULL){
			// nothing here, allocate, instantiate and add

			Tree *tree = (Tree*)malloc(sizeof(Tree));
			if(tree == NULL)
				exit(1);

			strcpy(tree->name, treeName);
			tree->val = 1;

			ha->arr[newIndex] = tree;
			ha->qty ++;

			return 1;

		}else {
			// something here, check if its the same tree i'm trying to add
			if(strcmp(treeName, ha->arr[newIndex]->name) == 0){
				ha->arr[newIndex]->val ++;
				return 1;
			}
		}
	}

	return 1;
}

void clearHash(Hash *ha){
	if(ha != NULL){
		for(int i = 0; i < MAXS; i++){
			if(ha->arr[i] != NULL){
				free(ha->arr[i]);
				ha->arr[i] = NULL;
			}
		}
		free(ha->arr);
		free(ha);
		ha = NULL;
	}
}

int compare(const void *p1, const void *p2){
	char str1[35], str2[35];
	Tree a = *(Tree*)p1;
	Tree b = *(Tree*)p2;

	return strcmp(a.name, b.name);
}

int main(){
	clock_t ttt = clock();

    int t, ch = false; scanf("%d", &t);
    scanf("%c%[^\n]", &buf, treeName); // read buffer and than empty line

    while(t--){
        if(ch)  printf("\n");
        int len = 0, count = 0, index = 0;
        Hash* ha = createHash();

        while(ha != NULL){
            scanf("%c%[^\n]",&buf, treeName);
            if(!strlen(treeName))   break; // end of test case if str length == 0
            count ++;

            insertHash(ha);

            memset(treeName, 0, sizeof(treeName));
        }

        //copy array
        int j = 0;
        for(int i = 0; i < MAXS; i++){
        	if(ha->arr[i] != NULL){
        		arrTree[j] = *(ha->arr[i]); 
        		j++;
        	}
        }

        qsort(arrTree, j, sizeof(struct tree), compare);

        for(int i = 0; i < j; i++){
	        float q = arrTree[i].val;
	        float value2 = (100.00/count)*q;
	        printf("%s %.4f\n", arrTree[i].name, value2);
        }

        memset(arrTree, 0, sizeof(arrTree));
        clearHash(ha);
        ch = true;
    }

    ttt = clock() - ttt;
    printf("Time elapsed: %f\n", (float)ttt/CLOCKS_PER_SEC);

    return 0;
}