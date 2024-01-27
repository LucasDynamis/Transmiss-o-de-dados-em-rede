//TAD árvore binária de busca com alocação encadeada (dinâmica)

//tipo exportado
//define o TipoItem que é o tipo dos elementos do TAD árvore binária de busca (clássica, AVL e B)
typedef struct
{
    int chave;
    char pacote;
    //outros campos
}TipoItem;

//tipo exportado
//define o TipoCelula que é o tipo das células que contêm os elementos que são manipulados pelo TAD árvore binária de busca (clássica ou AVL)
typedef struct celula
{
    TipoItem item;
    struct celula *esquerda;
    struct celula *direita;
    int balanco; // para o caso de a árvore ser AVL
}TipoCelula;

//-----TAD árvore binária de busca-----

//funções exportadas
//cria uma árvore binária de busca vazia
void CriaArvoreBinariaBuscaVazia(TipoCelula **arvore);

//testa se a árvore binária de busca é vazia
int TestaArvoreBinariaBuscaVazia(TipoCelula **arvore);

//busca por um elemento na árvore binária de busca
TipoItem * BuscaArvoreBinariaBusca(TipoCelula **arvore, int chave);

//insere um elemento do tipo TipoItem na árvore binária de busca
void InsereArvoreBinariaBusca(TipoCelula **arvore, TipoItem item);

//remove um elemento do tipo TipoItem da árvore binária de busca
void RemoveArvoreBinariaBusca(TipoCelula **arvore, TipoItem item);

//imprime os elementos da árvore binária de busca
void ImprimeArvoreBinariaBusca(TipoCelula **arvore, int l);
