/*****************************************************************//**
 * \file   Transporte.h
 * \brief  Transporte programa
 * 
 * \author gaspar
 * \date   March 2023
 *********************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)
#pragma once

enum tipostransporte
{
	trotinete,
	taxi,
	autocarro,
	bicicleta,
}tipostransporte;

#ifndef TransporteH
#define TransporteH
#define N 35
#define A 10

typedef struct Transporte {
	enum tipostransporte tipo;
	//struct Transporte* proximo;
	char local[50];
	float autonimia;
	double custo;
	bool alugado;

 }Transporte;

typedef struct listatransporte listatransporte;// separar o transporte do apontador proximo
typedef struct listatransporte {
	Transporte t;// transporte dentro da lista transporte 
	listatransporte* proximo;//apontador da lista
	listatransporte* primeiro;
	int tamanho;
}listatransporte;

// Assinaturas das fun��es

/**
 * brief
 * Fun��o que insere um novo transporte na lista ligada.
 */

bool inserirElemento(listatransporte* lista, Transporte elemento);

/**
 * brief
 * Fun��o que remove um transporte na lista ligada.
 */
bool removerElemento(listatransporte* lista, Transporte elemento);

/**
 * brief
 * Fun��o que altere um transporte na lista ligada..
 */
bool alterarElemento(listatransporte* lista, Transporte elementoAntigo, Transporte elementoNovo);

/**
 * brief
 * Fun�ao assistente a ordem decrescente de autonomia.
 */
void TrocarT(listatransporte* transport1, listatransporte* transport2);

/**
 * brief
 * Fun��o que ordena uma lista ligada de transportes em ordem decrescente de autonomia..
 */
bool ordemDecrescenteAutonomia(listatransporte* head);

/**
 * brief
 * Fun��o que lista os transportes por localiza��o..
 */
listatransporte* listarTransportePorLocalizacao(listatransporte* head, char* localizacao);

/**
 * brief
 * Fun�ao para o Registo do aluguer de um transporte.
 */
bool registarAluguer(struct listacliente* lista_clientes, struct listatransporte* lista_transportes, const char* nomeCliente, const char* localTransporte);

/**
 * brief
 * Fun��o que salva a lista ligada em um arquivo bin�rio.
 */
bool salvarTransporteBinario(struct listatransporte* lista, char* nomeArquivo);

/**
 * brief
 * Fun��o que l� a lista ligada de um arquivo bin�rio..
 */
bool carregarTransporteBinario(struct listatransporte** lista, char* nomeArquivo);

#endif// !TransporteH


