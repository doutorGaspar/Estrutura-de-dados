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

/**
* brief\
* (1º)A funçao apresentada demonstra os clientes que se encontram no ficheiro "Cliente.txt",
*  verificando tambem se o ficheiro existe.
*
 */
listacliente* Clientes();


#endif // !Clienteh
