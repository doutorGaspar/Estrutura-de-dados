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
#include <stdbool.h>
#include "Cliente.h"
#pragma warning(disable : 4996)

/**
* brief\
* (1º)A funçao apresentada demonstra os clientes que se encontram no ficheiro "Cliente.txt",
*  verificando tambem se o ficheiro existe.
* 
 */

listacliente* Clientes() {
	// 1º Verificar se o ficheiro existe
	FILE* ficheiro;
	listacliente* cliente = NULL;
	ficheiro = fopen("cliente.txt","r");
	if (ficheiro == NULL) {
		//printf("Erro ao abrir o ficheiro.\n");
		return false;
	}
	/**
	 * Fim da verificaçao.	 
	 */ 
	fclose(ficheiro);
	return cliente;
}

// 
/**
 * Função que insere um novo cliente na lista ligada
 * 
 * \param lista 
 * \param nome 
 * \param morada
 * \param nif
 * \param saldo
 */
bool inserirCliente(struct listacliente** lista, char nome[], char morada[], int nif, float saldo) {
	// Aloca memória para o novo cliente
	struct listacliente* novoCliente = (struct listacliente*)malloc(sizeof(struct cliente));
	if (novoCliente == NULL) return false;
	strcpy(novoCliente->c.nome, nome);
	strcpy(novoCliente->c.morada, morada);
	novoCliente->c.NIF = nif;
	novoCliente->c.saldoConta = saldo;
	novoCliente->proximo = NULL;

	// Insere o novo cliente no início da lista
	novoCliente->proximo = *lista;
	*lista = novoCliente;
}


/**
 * Função que remove um cliente da lista ligada.
 * 
 * \param lista
 * \param nif
 * \return 
 */
bool removerCliente(struct listacliente** lista, int nif) {// apontador para o apontador --> alterar o original na lista, nao ha copia
	// Procura pelo cliente na lista
	struct listacliente* atual = *lista;
	struct listacliente* anterior = NULL;
	while (atual != NULL && atual->c.NIF != nif) {
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


/**
 * Função que salva a lista ligada em um arquivo binário.
 * 
 * \param lista
 * \param nomeArquivo
 * \return 
 */
bool salvarClientesBinario(struct listacliente* lista, char* nomeArquivo) {
	FILE* ficheiro = fopen(nomeArquivo, "wb");
	if (ficheiro == NULL) {
		//printf("Erro ao abrir arquivo para escrita.\n");
		return false;
	}

	// Escreve o número de clientes no arquivo
	int numClientes = 0;
	struct listacliente* atual = lista;
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


/**
 * Função que lê a lista ligada de um arquivo binário.
 * 
 * \param lista
 * \param nomeArquivo
 * \return 
 */
bool carregarClientesBinario(struct listacliente** lista, char* nomeArquivo) {
	FILE* ficheiro = fopen(nomeArquivo, "rb");
	if (ficheiro == NULL) {
		//printf("Erro ao abrir arquivo para leitura.\n");
		return false;
	}

	// Lê o número de clientes do arquivo
	int numClientes;
	fread(&numClientes, sizeof(int), 1, ficheiro);

	// Lê cada cliente do arquivo e insere na lista ligada
	for (int i = 0; i < numClientes; i++) {
		struct listacliente* novoCliente = (struct listacliente*)malloc(sizeof(struct cliente));
		fread(novoCliente, sizeof(struct cliente), 1, ficheiro);
		novoCliente->proximo = *lista;
		*lista = novoCliente;
	}

	fclose(ficheiro);
}


/**
 * Função que altera os dados de um cliente na lista ligada.
 * 
 * \param lista
 * \param nif
 * \param novoNome
 * \param novaMorada
 * \param novoSaldo
 * \return 
 */
bool alterarCliente(struct cliente* lista, int nif, char novoNome[], char novaMorada[], float novoSaldo) {
	struct listacliente* atual = lista;
	while (atual != NULL) {
		if (atual->c.NIF == nif) {
			strcpy(atual->c.nome, novoNome);
			strcpy(atual->c.morada, novaMorada);
			atual->c.saldoConta = novoSaldo;
			return;
		}
		atual = atual->proximo;
	}
	//printf("Cliente com NIF %d nao encontrado.\n", nif);
	return;
}












