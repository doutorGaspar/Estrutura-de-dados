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

// Assinaturas das fun��es


/**
 * brief
 * Fun��o que insere um novo gestor na lista ligada.
 */
bool inserirDados(ListaGestores** lista, int id, const char* nome, const char* correio);

/**
 * brief
 * Fun��o que remove um gestor na lista ligada.
 */
bool removerDados(ListaGestores** lista, int id);

/**
 * brief
 * Fun��o que altere um cliente na lista ligada..
 */
bool alterarDados(ListaGestores* lista, int id, const char* novoNome, const char* novoCorreio);

/**
 * brief
 * Fun��o que salva a lista ligada em um arquivo bin�rio..
 */
bool salvarGestorBinario(struct ListaGestores* lista, char* nomeArquivo);

/**
 * brief
 * Fun��o que l� a lista ligada de um arquivo bin�rio..
 */
bool carregarGestorBinario(struct ListaGestores** lista, char* nomeArquivo);
#endif // !GestorH



