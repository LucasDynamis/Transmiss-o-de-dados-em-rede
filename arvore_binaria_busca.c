#include <stdio.h>
#include <stdlib.h>
#include "TAD_arvore_binaria_busca.h"

void Antecessor1(TipoCelula **arvore1, TipoCelula *arvore2);

//cria uma árvore binária de busca vazia
void CriaArvoreBinariaBuscaVazia(TipoCelula **arvore)
{
    *arvore = NULL;
}

//testa se a árvore binária de busca é vazia
int TestaArvoreBinariaBuscaVazia(TipoCelula **arvore)
{
    return (*arvore == NULL);
}

TipoItem * BuscaArvoreBinariaBusca(TipoCelula **arvore, int chave)
{
    if (TestaArvoreBinariaBuscaVazia(arvore))
        printf("Erro: item inexistente\n");
    else if (chave < (*arvore)->item.chave)
        BuscaArvoreBinariaBusca(&(*arvore)->esquerda, chave);
    else if (chave > (*arvore)->item.chave)
        BuscaArvoreBinariaBusca(&(*arvore)->direita, chave);
    else
        return &(*arvore)->item;
}

//insere um elemento do tipo TipoItem na árvore binária de busca
void InsereArvoreBinariaBusca(TipoCelula **arvore, TipoItem item)
{
    if (TestaArvoreBinariaBuscaVazia(arvore))
    {
        (*arvore) = (TipoCelula *)malloc(sizeof(TipoCelula));
        (*arvore)->item = item;
        (*arvore)->esquerda = (*arvore)->direita = NULL;
    }
    else if (item.chave < (*arvore)->item.chave)
        InsereArvoreBinariaBusca(&(*arvore)->esquerda, item);
    else if (item.chave > (*arvore)->item.chave)
        InsereArvoreBinariaBusca(&(*arvore)->direita, item);
    else
        printf("Erro: item existente\n");
}

//remove um elemento do tipo TipoItem da árvore binária de busca
void RemoveArvoreBinariaBusca(TipoCelula **arvore, TipoItem item)
{
    TipoCelula *aux;

    if (TestaArvoreBinariaBuscaVazia(arvore))
        printf("Erro: item inexistente\n");
    else if (item.chave < (*arvore)->item.chave)
        RemoveArvoreBinariaBusca(&(*arvore)->esquerda, item);
    else if (item.chave > (*arvore)->item.chave)
        RemoveArvoreBinariaBusca(&(*arvore)->direita, item);
    else if (TestaArvoreBinariaBuscaVazia(&(*arvore)->direita))
    {
        aux = *arvore;
        *arvore = (*arvore)->esquerda;
        free(aux);
    }
    else if (!TestaArvoreBinariaBuscaVazia(&(*arvore)->esquerda))
        Antecessor1(&(*arvore)->esquerda, *arvore);
    else
    {
        aux = *arvore;
        *arvore = (*arvore)->direita;
        free(aux);
    }
}

void Antecessor1(TipoCelula **arvore1, TipoCelula *arvore2)
{
    if (!TestaArvoreBinariaBuscaVazia(&(*arvore1)->direita))
        Antecessor1(&(*arvore1)->direita, arvore2);
    else
    {
        arvore2->item = (*arvore1)->item;
        arvore2 = *arvore1 ;
        *arvore1 = (*arvore1)->esquerda;
        free(arvore2);
    }
}

//imprime os elementos da árvore binária de busca
void ImprimeArvoreBinariaBusca(TipoCelula **arvore, int l)
{
    int i;

    if(!TestaArvoreBinariaBuscaVazia(arvore))
    {
        ImprimeArvoreBinariaBusca(&(*arvore)->esquerda, l + 1);
        for (i = 0; i < l; i++)
            printf("   ");
        printf("%i %c\n", (*arvore)->item.chave, (*arvore)->item.pacote);
        ImprimeArvoreBinariaBusca(&(*arvore)->direita, l + 1);
    }
}
