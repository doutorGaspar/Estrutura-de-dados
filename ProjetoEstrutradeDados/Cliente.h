/*****************************************************************//**
 * \file   Cliente.h
 * \brief  Cliente programa
 * 
 * \author gaspar
 * \date   March 2023
 *********************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#pragma warning(disable : 4996)
#pragma once

#ifndef Clienteh
#define Clienteh
#define N 35
#define A 10

typedef struct cliente {
	char nome[50];
	char morada[50];
	int NIF;
	double saldoConta;
}cliente;


typedef struct listacliente listacliente;// separar o cliente do apontador proximo
typedef struct listacliente {
	cliente c;// cliente dentro da lista cliente 
	listacliente* proximo;//apontador da lista
};

// Assinaturas das funções

/**
* brief
* A funçao apresentada demonstra os clientes que se encontram no ficheiro "Cliente.txt",
*  verificando tambem se o ficheiro existe.
 */
listacliente* Clientes();

/**
 * brief
 * Função que insere um novo cliente na lista ligada.
 */
bool inserirCliente(struct listacliente** lista, char nome[], char morada[], int nif, float saldo);

/**
 * brief
 * Função que remove um cliente da lista ligada..
 */
bool removerCliente(struct listacliente** lista, int nif);

/**
 * brief
 * Função que salva a lista ligada em um arquivo binário..
 */
bool salvarClientesBinario(struct listacliente* lista, char* nomeArquivo);

/**
 * brief
 * Função que lê a lista ligada de um arquivo binário..
 */
bool carregarClientesBinario(struct listacliente** lista, char* nomeArquivo);

/**
 * brief
 * Função que altera os dados de um cliente na lista ligada..
 */
bool alterarCliente(struct cliente* lista, int nif, char novoNome[], char novaMorada[], float novoSaldo);

#endif // !Clienteh
