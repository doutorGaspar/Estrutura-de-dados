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

// Assinaturas das funções

/**
 * brief
 * Função para criar um novo vértice no grafo.
 */
Vertice* criarVertice(char localizacao[], cliente cliente, Transporte transporte);

/**
 * brief
 * Função para criar uma nova aresta entre dois vértices.
 */
Aresta* criarAresta(Vertice* destino, double custo);

/**
 * brief
 * Função para adicionar um vértice ao grafo.
 */
bool adicionarVertice(Grafo* grafo, Vertice* novoVertice);

/**
 * brief
 * Função para adicionar uma aresta entre dois vértices.
 */
bool adicionarAresta(Vertice* origem, Vertice* destino, double custo);

/**
 * brief
 * Função para liberar a memória alocada pelo grafo.
 */
bool liberarGrafo(Grafo* grafo);

/**
 * brief
 * Funçao que salva o ficheiro grafo em txt.
 */
bool salvarGrafoTexto(Grafo* grafo, const char* nomeArquivo);

/**
 * brief
 * Funçao que salva o Ficheiro Grafo txt em binario.
 */
bool salvarGrafoBinario(Grafo* grafo, const char* nomeArquivo);

/**
 * brief
 * Função que encontra um vértice em um grafo pelo seu nome de localização.
 */
Vertice* encontrarVertice(Grafo* grafo, const char* localizacao);

/**
 * brief
 * Função que cria um novo grafo.
 */
Grafo* criarGrafo();

/**
 * brief
 * Funçao que carrega o ficheiro txt para binario do Grafo.
 */
Grafo* carregarGrafoBinario(const char* nomeArquivo);

/**
 * brief
 * Função para exibir as informações de todos os vértices e suas arestas no grafo.
 */
bool exibirGrafo(Grafo* grafo);




