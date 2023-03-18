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
	cliente* proximo;
}cliente;

#endif // !Clienteh
