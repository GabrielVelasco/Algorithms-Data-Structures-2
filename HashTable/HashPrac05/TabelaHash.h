//Potências de dois devem ser evitadas
//deve ser um número primo distante de pequenas potências de dois

struct aluno{
    int matricula;
    char nome[50];
    int n1,n2,n3;

};

struct galo{
	int key; // key separada da struct
	void *item;

};

typedef struct hash Hash;
typedef struct aluno Aluno;
typedef struct galo Galo;

Hash* criaHash(int TABLE_SIZE, int);
void liberaHash(Hash* ha);
// void printHash(Hash*);
void reallocTable(Hash**, int);
// int valorString(char *str);
// int insereHash_SemColisao(Hash* ha, struct aluno al);
// int buscaHash_SemColisao(Hash* ha, int mat, struct aluno* al);
int insereHash_EnderAberto(Hash* ha, void *al, int);
int buscaHash_EnderAberto(Hash* ha, int mat, void* al);
int tamanhoHash(Hash*);

/*
int chaveDivisao(int chave, int TABLE_SIZE);
int chaveDobra(int chave, int TABLE_SIZE);
int chaveMultiplicacao(int chave, int TABLE_SIZE);
int sondagemLinear(int pos, int i, int TABLE_SIZE);
int sondagemQuadratica(int pos, int i, int TABLE_SIZE);
int duploHashing(int pos, int chave, int i, int TABLE_SIZE);
*/
