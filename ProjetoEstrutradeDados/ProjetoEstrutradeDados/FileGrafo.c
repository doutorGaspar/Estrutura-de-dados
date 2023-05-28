/*****************************************************************//**
 * \file   FileGrafo.c
 * \brief  Funçoes para o Grafo
 * 
 * \author gaspar
 * \date   May 2023
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"
#pragma warning(disable : 4996)

/**
 * Função para criar um novo vértice no grafo.
 * 
 * \param localizacao
 * \param cliente
 * \param transporte
 * \return 
 */
Vertice* criarVertice(char localizacao[], cliente cliente, Transporte transporte) {
    Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
    if (novoVertice != NULL) {
        strcpy(novoVertice->localizacao, localizacao);
        novoVertice->cliente = cliente;
        novoVertice->transporte = transporte;
        novoVertice->arestas = NULL;
        novoVertice->proximo = NULL;
    }
    return novoVertice;
}

/**
 * Função para criar uma nova aresta entre dois vértices.
 * 
 * \param destino
 * \param custo
 * \return 
 */
Aresta* criarAresta(Vertice* destino, double custo) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    if (novaAresta != NULL) {
        novaAresta->destino = destino;
        novaAresta->custo = custo;
        novaAresta->proxima = NULL;
    }
    return novaAresta;
}


/**
 * Função para adicionar um vértice ao grafo.
 * 
 * \param grafo
 * \param novoVertice
 */
bool adicionarVertice(Grafo* grafo, Vertice* novoVertice) {
    if (grafo->vertices == NULL) {
        grafo->vertices = novoVertice;
    }
    else {
        Vertice* atual = grafo->vertices;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoVertice;
    }
}

/**
 * Função para adicionar uma aresta entre dois vértices.
 * 
 * \param origem
 * \param destino
 * \param custo
 */
bool adicionarAresta(Vertice* origem, Vertice* destino, double custo) {
    Aresta* novaAresta = criarAresta(destino, custo);
    if (novaAresta != NULL) {
        if (origem->arestas == NULL) {
            origem->arestas = novaAresta;
        }
        else {
            Aresta* atual = origem->arestas;
            while (atual->proxima != NULL) {
                atual = atual->proxima;
            }
            atual->proxima = novaAresta;
        }
    }
}


/**
 * Função para liberar a memória alocada pelo grafo.
 * 
 * \param grafo
 */
bool liberarGrafo(Grafo* grafo) {
    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        Aresta* arestaAtual = atual->arestas;
        while (arestaAtual != NULL) {
            Aresta* proximaAresta = arestaAtual->proxima;
            free(arestaAtual);
            arestaAtual = proximaAresta;
        }

        Vertice* proximoVertice = atual->proximo;
        free(atual);
        atual = proximoVertice;
    }

    grafo->vertices = NULL;
}

bool salvarGrafoTexto(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        // Escreve a localização do vértice no arquivo
        fprintf(arquivo, "Localizacao: %s\n", atual->localizacao);

        // Escreve os dados do cliente no arquivo
        fprintf(arquivo, "Cliente: %s\n", atual->cliente.nome);

        // Escreve os dados do transporte no arquivo
        fprintf(arquivo, "Transporte: %s\n", atual->transporte.local);

        // Separador entre vértices
        fprintf(arquivo, "-----\n");

        Aresta* arestaAtual = atual->arestas;
        while (arestaAtual != NULL) {
            // Escreve o destino da aresta no arquivo
            fprintf(arquivo, "Aresta para: %s\n", arestaAtual->destino->localizacao);

            // Escreve o custo da aresta no arquivo
            fprintf(arquivo, "Custo: %lf\n", arestaAtual->custo);

            // Separador entre arestas
            fprintf(arquivo, "-----\n");

            arestaAtual = arestaAtual->proxima;
        }

        atual = atual->proximo;
    }

    fclose(arquivo);
}

bool salvarGrafoBinario(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        // Escreve a estrutura do vértice diretamente no arquivo
        fwrite(atual, sizeof(Vertice), 1, arquivo);

        Aresta* arestaAtual = atual->arestas;
        while (arestaAtual != NULL) {
            // Escreve a estrutura da aresta diretamente no arquivo
            fwrite(arestaAtual, sizeof(Aresta), 1, arquivo);

            arestaAtual = arestaAtual->proxima;
        }

        atual = atual->proximo;
    }

    fclose(arquivo);
}

#pragma region Exibicao
/**
 * Função para exibir as informações de todos os vértices e suas arestas no grafo.
 * 
 * \param grafo
 */
bool exibirGrafo(Grafo* grafo) {
    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        printf("Localizacao: %s\n", atual->localizacao);
        printf("Cliente: %s\n", atual->cliente.nome);
        printf("Meio de Transporte: %s\n", atual->transporte.tipo);

        Aresta* arestaAtual = atual->arestas;
        while (arestaAtual != NULL) {
            printf("  -> Destino: %s, Custo: %.2f\n", arestaAtual->destino->localizacao, arestaAtual->custo);
            arestaAtual = arestaAtual->proxima;
        }

        atual = atual->proximo;
        printf("\n");
    }
}
#pragma endregion

