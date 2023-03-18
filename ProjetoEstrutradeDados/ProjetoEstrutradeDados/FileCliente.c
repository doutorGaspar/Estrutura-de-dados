/*****************************************************************//**
 * \file   FileCliente.c
 * \brief  funçoes do Cliente
 * 
 * \author gaspar
 * \date   March 2023
 *********************************************************************/
#include <stdio.h>// Inclui a biblioteca padrão de entrada e saída.
#include <stdlib.h>//Inclui a biblioteca padrão para alocação de memória.
#include <string.h>//Inclui a biblioteca padrão de manipulação de strings.
#include "Cliente.h"
#define _CTR_SECURE_NO_WARNINGS

/**
* brief\
* (1º)A funçao apresentada demonstra os clientes que se encontram no ficheiro "Cliente.txt",
*  verificando tambem se o ficheiro existe.
* 
 */

cliente* Clientes() {
	// 1º Verificar se o ficheiro existe
	FILE* ficheiro;
	cliente* cliente;
	ficheiro = fopen("cliente.txt","r");
	if (ficheiro == NULL) {
		printf("Erro ao abrir o ficheiro.\n");
		return;
	}
	/**
	 * Fim da verificaçao.	 
	 */ 
	fclose(ficheiro);
	return cliente;
}

// Função que insere um novo cliente na lista ligada
void inserirCliente(struct cliente** lista, char nome[], char morada[], int nif, float saldo) {
	// Aloca memória para o novo cliente
	struct cliente* novoCliente = (struct cliente*)malloc(sizeof(struct cliente));
	strcpy(novoCliente->nome, nome);
	strcpy(novoCliente->morada, morada);
	novoCliente->NIF = nif;
	novoCliente->saldoConta = saldo;
	novoCliente->proximo = NULL;

	// Insere o novo cliente no início da lista
	novoCliente->proximo = *lista;
	*lista = novoCliente;
}

// Função que remove um cliente da lista ligada
void removerCliente(struct cliente** lista, int nif) {
	// Procura pelo cliente na lista
	struct cliente* atual = *lista;
	struct cliente* anterior = NULL;
	while (atual != NULL && atual->NIF != nif) {
		anterior = atual;
		atual = atual->proximo;
	}

	// Se o cliente foi encontrado, remove-o da lista
	if (atual != NULL) {
		if (anterior == NULL) {
			*lista = atual->proximo;
		}
		else {
			anterior->proximo = atual->proximo;
		}
		free(atual);
	}
}

// Função que salva a lista ligada em um arquivo binário
void salvarClientesBinario(struct cliente* lista, char* nomeArquivo) {
	FILE* ficheiro = fopen(nomeArquivo, "wb");
	if (ficheiro == NULL) {
		printf("Erro ao abrir arquivo para escrita.\n");
		return;
	}

	// Escreve o número de clientes no arquivo
	int numClientes = 0;
	struct cliente* atual = lista;
	while (atual != NULL) {
		numClientes++;
		atual = atual->proximo;
	}
	fwrite(&numClientes, sizeof(int), 1, ficheiro);

	// Escreve cada cliente no arquivo
	atual = lista;
	while (atual != NULL) {
		fwrite(atual, sizeof(struct cliente), 1, ficheiro);
		atual = atual->proximo;
	}

	fclose(ficheiro);
}

// Função que lê a lista ligada de um arquivo binário
void carregarClientesBinario(struct cliente** lista, char* nomeArquivo) {
	FILE* ficheiro = fopen(nomeArquivo, "rb");
	if (ficheiro == NULL) {
		printf("Erro ao abrir arquivo para leitura.\n");
		return;
	}

	// Lê o número de clientes do arquivo
	int numClientes;
	fread(&numClientes, sizeof(int), 1, ficheiro);

	// Lê cada cliente do arquivo e insere na lista ligada
	for (int i = 0; i < numClientes; i++) {
		struct cliente* novoCliente = (struct cliente*)malloc(sizeof(struct cliente));
		fread(novoCliente, sizeof(struct cliente), 1, ficheiro);
		novoCliente->proximo = *lista;
		*lista = novoCliente;
	}

	fclose(ficheiro);
}

//leitura em txt
//salvar em binario











