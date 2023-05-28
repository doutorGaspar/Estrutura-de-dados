/*****************************************************************//**
 * \file   Grafo.h
 * \brief  Grafo Programa
 * 
 * \author gaspar
 * \date   May 2023
 *********************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Transporte.h"
#include "Cliente.h"
#pragma warning(disable : 4996)
#pragma once


typedef struct Vertice {
    char localizacao[50];
    cliente cliente;
    Transporte transporte;
    struct Aresta* arestas;
    struct Vertice* proximo;
} Vertice;

typedef struct Aresta {
    struct Vertice* destino;
    double custo;
    struct Aresta* proxima;
} Aresta;

typedef struct Grafo {
    Vertice* vertices;
} Grafo;

// Assinaturas das fun��es

/**
 * brief
 * Fun��o para criar um novo v�rtice no grafo.
 */
Vertice* criarVertice(char localizacao[], cliente cliente, Transporte transporte);

/**
 * brief
 * Fun��o para criar uma nova aresta entre dois v�rtices.
 */
Aresta* criarAresta(Vertice* destino, double custo);

/**
 * brief
 * Fun��o para adicionar um v�rtice ao grafo.
 */
bool adicionarVertice(Grafo* grafo, Vertice* novoVertice);

/**
 * brief
 * Fun��o para adicionar uma aresta entre dois v�rtices.
 */
bool adicionarAresta(Vertice* origem, Vertice* destino, double custo);

/**
 * brief
 * Fun��o para liberar a mem�ria alocada pelo grafo.
 */
bool liberarGrafo(Grafo* grafo);

/**
 * brief
 * Fun�ao que salva o ficheiro grafo em txt.
 */
bool salvarGrafoTexto(Grafo* grafo, const char* nomeArquivo);

/**
 * brief
 * Fun�ao que salva o Ficheiro Grafo txt em binario.
 */
bool salvarGrafoBinario(Grafo* grafo, const char* nomeArquivo);

/**
 * brief
 * Fun��o que encontra um v�rtice em um grafo pelo seu nome de localiza��o.
 */
Vertice* encontrarVertice(Grafo* grafo, const char* localizacao);

/**
 * brief
 * Fun��o que cria um novo grafo.
 */
Grafo* criarGrafo();

/**
 * brief
 * Fun�ao que carrega o ficheiro txt para binario do Grafo.
 */
Grafo* carregarGrafoBinario(const char* nomeArquivo);

/**
 * brief
 * Fun��o para exibir as informa��es de todos os v�rtices e suas arestas no grafo.
 */
bool exibirGrafo(Grafo* grafo);




