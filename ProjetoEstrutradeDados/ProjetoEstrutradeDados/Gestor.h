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

#endif // !GestorH
