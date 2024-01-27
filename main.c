#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "TAD_arvore_binaria_busca.h"

void SolicitarMensagem(char mensagem[], int tamanho);
void FragmentarMensagem(TipoCelula **arvore, char mensagem[]);
void GerarReplicacao(TipoCelula *no);
void EmbaralharPacotes(TipoCelula **arvore);
void ConstruirArvore(TipoCelula **arvore, TipoCelula *pacote);
void ImprimirSequencia(TipoCelula *pacote);
void ImprimirSequenciaEmbaralhada(TipoCelula *pacote);
void ImprimirArvore(TipoCelula **arvore);
void ReconstruirMensagem(TipoCelula *arvore, char mensagem[], int *indice);
void ImprimirMensagemOriginal(char mensagem[], int tamanho);

int main()
{
    srand(time(NULL));

    TipoCelula *arvore;
    CriaArvoreBinariaBuscaVazia(&arvore);

    char mensagem[100];
    SolicitarMensagem(mensagem, sizeof(mensagem));

    FragmentarMensagem(&arvore, mensagem);
    ImprimirSequencia(arvore);

    EmbaralharPacotes(&arvore);
    ImprimirSequenciaEmbaralhada(arvore);

    TipoCelula *arvoreReconstruida = NULL;
    ConstruirArvore(&arvoreReconstruida, arvore);
    ImprimirArvore(&arvoreReconstruida);

    char mensagemReconstruida[100];
    int indice = 0;
    ReconstruirMensagem(arvoreReconstruida, mensagemReconstruida, &indice);
    ImprimirMensagemOriginal(mensagemReconstruida, indice);

    return 0;
}

void SolicitarMensagem(char mensagem[], int tamanho)
{
    printf("Digite a mensagem a ser transmitida: ");
    fgets(mensagem, tamanho, stdin);

    // Remover o caractere de nova linha no final da string
    mensagem[strcspn(mensagem, "\n")] = '\0';
}

void FragmentarMensagem(TipoCelula **arvore, char mensagem[])
{
    int tamanho = strlen(mensagem);
    for (int i = 0; i < tamanho; i++)
    {
        TipoItem item;
        item.chave = i;
        item.pacote = mensagem[i];

        InsereArvoreBinariaBusca(arvore, item);
        TipoItem *itemEncontrado = BuscaArvoreBinariaBusca(arvore, i);
        TipoCelula *no = (TipoCelula *)itemEncontrado;
        GerarReplicacao(no);
    }
}

void GerarReplicacao(TipoCelula *no)
{
    int replicacao = rand() % 10 + 1; // Gera um número aleatório entre 1 e 10

    for (int i = 0; i < replicacao; i++)
    {
        TipoCelula *novo = (TipoCelula *)malloc(sizeof(TipoCelula));
        novo->item = no->item;
        novo->esquerda = novo->direita = NULL;

        if (no->direita == NULL)
            no->direita = novo;
        else
        {
            TipoCelula *ultimo = no->direita;
            while (ultimo->direita != NULL)
                ultimo = ultimo->direita;
            ultimo->direita = novo;
        }
    }
}

void EmbaralharPacotes(TipoCelula **arvore)
{
    if (*arvore == NULL)
        return;

    TipoCelula *pacote = *arvore;
    TipoCelula *embaralhado = NULL;

    while (pacote != NULL)
    {
        TipoCelula *prox = pacote->direita;

        pacote->direita = embaralhado;
        embaralhado = pacote;

        pacote = prox;
    }

    *arvore = embaralhado;
}

void ConstruirArvore(TipoCelula **arvore, TipoCelula *pacote)
{
    if (pacote == NULL)
        return;

    ConstruirArvore(arvore, pacote->esquerda);
    ConstruirArvore(arvore, pacote->direita);

    InsereArvoreBinariaBusca(arvore, pacote->item);
}

void ImprimirSequencia(TipoCelula *pacote)
{
    printf("Sequência de pacotes original:\n");
    while (pacote != NULL)
    {
        printf("%c ", pacote->item.pacote);
        pacote = pacote->direita;
    }
    printf("\n");
}

void ImprimirSequenciaEmbaralhada(TipoCelula *pacote)
{
    printf("Nova sequência de pacotes embaralhados:\n");
    while (pacote != NULL)
    {
        printf("%c ", pacote->item.pacote);
        pacote = pacote->direita;
    }
    printf("\n");
}

void ImprimirArvore(TipoCelula **arvore)
{
    printf("Árvore binária de busca:\n");
    ImprimeArvoreBinariaBusca(arvore, 0);
}

void ReconstruirMensagem(TipoCelula *arvore, char mensagem[], int *indice)
{
    if (arvore == NULL)
        return;

    ReconstruirMensagem(arvore->esquerda, mensagem, indice);
    mensagem[*indice] = arvore->item.pacote;
    (*indice)++;
    ReconstruirMensagem(arvore->direita, mensagem, indice);
}

void ImprimirMensagemOriginal(char mensagem[], int tamanho)
{
    printf("Mensagem original reconstruída:\n");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%c", mensagem[i]);
    }
    printf("\n");
}
