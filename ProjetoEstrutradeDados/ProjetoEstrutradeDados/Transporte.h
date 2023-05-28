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


#endif// !TransporteH
