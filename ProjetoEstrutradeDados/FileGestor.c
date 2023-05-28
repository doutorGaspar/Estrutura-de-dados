/*****************************************************************//**
 * \file   FileGestor.c
 * \brief  Funçoes do Gestor
 * 
 * \author gaspar
 * \date   March 2023
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Gestor.h"
#pragma warning(disable : 4996)

/**
 * Função que insere um novo gestor na lista ligada.
 * 
 * \param lista
 * \param id
 * \param nome
 * \param correio
 * \return 
 */
bool inserirDados(ListaGestores** lista, int id, const char* nome, const char* correio) {
    ListaGestores* novo = (ListaGestores*)malloc(sizeof(ListaGestores));
    if (novo == NULL) {
        return false;
    }

    novo->g.id = id;
    strncpy(novo->g.nome, nome, N);
    strncpy(novo->g.correiemail, correio, N);

    novo->proximo = *lista;
    *lista = novo;
    return true;
}

/**
 * Função que remove um gestor na lista ligada.
 * 
 * \param lista
 * \param id
 * \return 
 */
bool removerDados(ListaGestores** lista, int id) {
    ListaGestores* atual = *lista;
    ListaGestores* anterior = NULL;

    while (atual != NULL) {
        if (atual->g.id == id) {
            if (anterior == NULL) {
                *lista = atual->proximo;
            }
            else {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            return true;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    return false;
}
/**
 * Função que altere um cliente na lista ligada.
 * 
 * \param lista
 * \param id
 * \param novoNome
 * \param novoCorreio
 * \return 
 */
bool alterarDados(ListaGestores* lista, int id, const char* novoNome, const char* novoCorreio) {
    ListaGestores* atual = lista;

    while (atual != NULL) {
        if (atual->g.id == id) {
            strncpy(atual->g.nome, novoNome, N);
            strncpy(atual->g.correiemail, novoCorreio, N);

            return true;
        }

        atual = atual->proximo;
    }

    return false;
}


/**
 * Função que salva a lista ligada em um arquivo binário.
 * 
 * \param lista
 * \param nomeArquivo
 * \return 
 */
bool salvarGestorBinario(struct ListaGestores* lista, char* nomeArquivo) {
    FILE* ficheiro = fopen(nomeArquivo, "wb");
    if (ficheiro == NULL) {
        //printf("Erro ao abrir arquivo para escrita.\n");
        return false;
    }

    // Escreve o número de gestores no arquivo
    int numGestor = 0;
    struct ListaGestores* atual = lista;
    while (atual != NULL) {
        numGestor++;
        atual = atual->proximo;
    }
    fwrite(&numGestor, sizeof(int), 1, ficheiro);

    // Escreve cada gestor no arquivo
    atual = lista;
    while (atual != NULL) {
        fwrite(atual, sizeof(struct Gestor), 1, ficheiro);
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
bool carregarGestorBinario(struct ListaGestores** lista, char* nomeArquivo) {
    FILE* ficheiro = fopen(nomeArquivo, "rb");
    if (ficheiro == NULL) {
        //printf("Erro ao abrir arquivo para leitura.\n");
        return false;
    }

    // Lê o número de gestores do arquivo
    int numGestor;
    fread(&numGestor, sizeof(int), 1, ficheiro);

    // Lê cada gestores do arquivo e insere na lista ligada
    for (int i = 0; i < numGestor; i++) {
        struct ListaGestores* novo = (struct ListaGestores*)malloc(sizeof(struct Gestor));
        fread(novo, sizeof(struct Gestor), 1, ficheiro);
        novo->proximo = *lista;
        *lista = novo;
    }

    fclose(ficheiro);
}