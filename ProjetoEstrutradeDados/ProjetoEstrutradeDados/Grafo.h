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


