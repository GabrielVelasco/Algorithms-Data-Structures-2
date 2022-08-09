struct aluno{
	int matricula;
	char nome[50];
	
 };

typedef struct hash Hash;
typedef struct aluno Aluno;

Hash* createHash(int);
int linearProbing(int, int, int);
int insertHash(Hash*, Aluno);
int buscaHash(Hash*, int, Aluno*);
void clearHash(Hash*);
void printHash(Hash*);