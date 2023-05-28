/*****************************************************************//**
 * \file   Gestor.h
 * \brief  Gestor programa
 * 
 * \author gaspar
 * \date   March 2023
 *********************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)
#pragma once

#ifndef GestorH
#define GestorH
#define N 35
#define A 10

typedef struct Gestor {
	int id;
	char nome[N];
	char correiemail[N];
}Gestor;

typedef struct ListaGestores ListaGestores;
typedef struct ListaGestores {
	Gestor g;
	struct ListaGestores* proximo;
}ListaGestores;

// Assinaturas das funções


/**
 * brief
 * Função que insere um novo gestor na lista ligada.
 */
bool inserirDados(ListaGestores** lista, int id, const char* nome, const char* correio);

/**
 * brief
 * Função que remove um gestor na lista ligada.
 */
bool removerDados(ListaGestores** lista, int id);

/**
 * brief
 * Função que altere um cliente na lista ligada..
 */
bool alterarDados(ListaGestores* lista, int id, const char* novoNome, const char* novoCorreio);

/**
 * brief
 * Função que salva a lista ligada em um arquivo binário..
 */
bool salvarGestorBinario(struct ListaGestores* lista, char* nomeArquivo);

/**
 * brief
 * Função que lê a lista ligada de um arquivo binário..
 */
bool carregarGestorBinario(struct ListaGestores** lista, char* nomeArquivo);
#endif // !GestorH



