struct aluno{
    int matricula;
    char nome[50];
    int n1, n2, n3;
};

struct item{
    int key;
    void* genericData;
};

typedef struct hash Hash;
typedef struct item Item;

Hash* criaHash(int TABLE_SIZE, int TYPE_SIZE);
void liberaHash(Hash* ht);
int insereHash(Hash **ht, void* genericData, int key);
int buscaHash(Hash* ht, void* genericData, int key);