#define TAM_ALFABETO 26
typedef struct trieNode* Trie;

Trie* criaTrie();
int insereTrie(Trie* tr, char *str);
int buscaTrie(Trie* tr, char *str);
//int arvoreComFilhos(Trie* tr);
int removeTrie(Trie* tr, char *str);
void imprimeTrie(Trie* tr);
//void imprimeAux(Trie* tr, char *str, int pos);