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
#pragma once


#ifndef TransporteH
#define TransporteH
#define N 35
#define A 10

typedef struct Transporte {
	char meioDetransporte[50];
	float autonimia;
	double custo;

 }Transporte;

#endif// !TransporteH
