/*****************************************************************//**
 * \file   FileCliente.c
 * \brief  fun�oes do Cliente
 * 
 * \author gaspar
 * \date   March 2023
 *********************************************************************/
#include <stdio.h>// Inclui a biblioteca padr�o de entrada e sa�da.
#include <stdlib.h>//Inclui a biblioteca padr�o para aloca��o de mem�ria.
#include <string.h>//Inclui a biblioteca padr�o de manipula��o de strings.
#include "Cliente.h"
#define _CTR_SECURE_NO_WARNINGS

/**
* brief\
* (1�)A fun�ao apresentada demonstra os clientes que se encontram no ficheiro "Cliente.txt",
*  verificando tambem se o ficheiro existe.
* 
 */

cliente* Clientes() {
	// 1� Verificar se o ficheiro existe
	FILE* ficheiro;
	cliente* cliente;
	ficheiro = fopen("cliente.txt","r");
	if (ficheiro == NULL) {
		printf("Erro ao abrir o ficheiro.\n");
		return;
	}
	/**
	 * Fim da verifica�ao.	 
	 */ 
	fclose(ficheiro);
	return cliente;
}

// Fun��o que insere um novo cliente na lista ligada
void inserirCliente(struct cliente** lista, char nome[], char morada[], int nif, float saldo) {
	// Aloca mem�ria para o novo cliente
	struct cliente* novoCliente = (struct cliente*)malloc(sizeof(struct cliente));
	strcpy(novoCliente->nome, nome);
	strcpy(novoCliente->morada, morada);
	novoCliente->NIF = nif;
	novoCliente->saldoConta = saldo;
	novoCliente->proximo = NULL;

	// Insere o novo cliente no in�cio da lista
	novoCliente->proximo = *lista;
	*lista = novoCliente;
}

// Fun��o que remove um cliente da lista ligada
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

// Fun��o que salva a lista ligada em um arquivo bin�rio
void salvarClientesBinario(struct cliente* lista, char* nomeArquivo) {
	FILE* ficheiro = fopen(nomeArquivo, "wb");
	if (ficheiro == NULL) {
		printf("Erro ao abrir arquivo para escrita.\n");
		return;
	}

	// Escreve o n�mero de clientes no arquivo
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

// Fun��o que l� a lista ligada de um arquivo bin�rio
void carregarClientesBinario(struct cliente** lista, char* nomeArquivo) {
	FILE* ficheiro = fopen(nomeArquivo, "rb");
	if (ficheiro == NULL) {
		printf("Erro ao abrir arquivo para leitura.\n");
		return;
	}

	// L� o n�mero de clientes do arquivo
	int numClientes;
	fread(&numClientes, sizeof(int), 1, ficheiro);

	// L� cada cliente do arquivo e insere na lista ligada
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











