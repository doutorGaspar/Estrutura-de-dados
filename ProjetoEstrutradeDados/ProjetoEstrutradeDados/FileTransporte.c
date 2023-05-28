/*****************************************************************//**
 * \file   FileTransporte.c
 * \brief  Funçoes para o transporte
 * 
 * \author gaspar
 * \date   March 2023
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Transporte.h"
#include "Cliente.h"
#pragma warning(disable : 4996)


/**
 * Função que insere um novo transporte na lista ligada.
 * 
 * \param lista
 * \param elemento
 * \return 
 */
bool inserirElemento(listatransporte* lista, Transporte elemento) {
    listatransporte* novoElemento = (listatransporte*)malloc(sizeof(listatransporte));
    if (novoElemento == NULL) {
        return false;  // Falha na alocação de memória
    }
    novoElemento->t = elemento;
    novoElemento->proximo = lista->primeiro;
    lista->primeiro = novoElemento;
    lista->tamanho++;
    return true;  // Inserção bem-sucedida
}
/**
 * Função que remove um transporte na lista ligada.
 * 
 * \param lista
 * \param elemento
 * \return 
 */
bool removerElemento(listatransporte* lista, Transporte elemento) {
    listatransporte* anterior = NULL;
    listatransporte* atual = lista->primeiro;
    while (atual != NULL) {
        if (atual->t.tipo == elemento.tipo && strcmp(atual->t.local, elemento.local) == 0) {
            if (anterior == NULL) {
                lista->primeiro = atual->proximo;
            }
            else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            lista->tamanho--;
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

/**
 * Função que altere um transporte na lista ligada.
 * 
 * \param lista
 * \param elementoAntigo
 * \param elementoNovo
 * \return 
 */
bool alterarElemento(listatransporte* lista, Transporte elementoAntigo, Transporte elementoNovo) {
    listatransporte* atual = lista->primeiro;
    while (atual != NULL) {
        if (atual->t.tipo == elementoAntigo.tipo && strcmp(atual->t.local, elementoAntigo.local) == 0) {
            atual->t = elementoNovo;
            return;
        }
        atual = atual->proximo;
    }
}
/**
 * Funçao assistente a ordem decrescente de autonomia.
 * 
 * \param transport1
 * \param transport2
 */
void TrocarT(listatransporte* transport1, listatransporte* transport2) {

    Transporte aux = transport1->t;
    transport1->t = transport2->t;
    transport2->t = aux;
}

/**
 * Funçao para a listagem dos meios de transporte por ordem decrescente de autonomia;.
 * 
 * \param head
 * \return 
 */
bool ordemDecrescenteAutonomia(listatransporte* head) {
    if (head == NULL) return false;

    bool isSorted = false;
    listatransporte* current = NULL;

    while (!isSorted)
    {
        isSorted = true;
        current = head;
        while (current->proximo != NULL)
        {
            if (current->t.autonimia < current->proximo->t.autonimia) {
                TrocarT(current, current->proximo);
                isSorted = false;
            }
            current = current->proximo;
        }
    }
    return true;
}
/**
 * Funçao para o geocodigo.
 * 
 * \param head
 * \param localizacao
 * \return 
 */


//Geocodigo
listatransporte* listarTransportePorLocalizacao(listatransporte* head, char* localizacao) {

    if (head == NULL)return NULL;
    listatransporte* ultimoAutomovel = NULL;
    listatransporte* novaLista = NULL;
    listatransporte* aux = head;
    while (aux != NULL) {
        if (strcmp(aux->t.local, localizacao) == 0) {
            listatransporte* novoAutomovel = (listatransporte*)malloc(sizeof(listatransporte));
            novoAutomovel->t = aux->t;
            novoAutomovel->proximo = NULL;

            if (novaLista == NULL) {
                novaLista = novoAutomovel;
                ultimoAutomovel = novaLista;
            }
            else {
                ultimoAutomovel->proximo = novoAutomovel;
                ultimoAutomovel = novoAutomovel;

            }
        }
        aux = aux->proximo;
    }
    return novaLista;
}

/**
 * Funçao para o Registo do aluguer de um transporte.
 * 
 * \param lista_clientes
 * \param lista_transportes
 * \param nomeCliente
 * \param localTransporte
 * \return 
 */
bool registarAluguer(struct listacliente* lista_clientes, struct listatransporte* lista_transportes, const char* nomeCliente, const char* localTransporte) {
    // Verificar se o cliente existe na lista de clientes
    struct listacliente* clienteAtual = lista_clientes;
    while (clienteAtual != NULL) {
        if (strcmp(clienteAtual->c.nome, nomeCliente) == 0) {
            // Cliente encontrado, verificar se o cliente possui saldo suficiente
            if (clienteAtual->c.saldoConta >= lista_transportes->t.custo) {
                // Verificar se o meio de transporte existe e está disponível para aluguer
                struct listatransporte* transporteAtual = lista_transportes;
                while (transporteAtual != NULL) {
                    if (strcmp(transporteAtual->t.local, localTransporte) == 0) {
                        if (transporteAtual->t.alugado) {
                            printf("Meio de transporte indisponível para aluguer.\n");
                            return;
                        }
                        else {
                            // Registar o aluguer do cliente
                            clienteAtual->c.saldoConta -= transporteAtual->t.custo;
                            // Marcar o meio de transporte como alugado
                            transporteAtual->t.alugado = true;
                            printf("Aluguer registado com sucesso.\n");
                            return;
                        }
                    }
                    transporteAtual = transporteAtual->proximo;
                }
                printf("Meio de transporte nao encontrado.\n");
                return;
            }
            else {
                printf("Saldo insuficiente na conta do cliente.\n");
                return;
            }
        }
        clienteAtual = clienteAtual->proximo;
    }

    // Cliente não encontrado
    printf("Cliente nao encontrado.\n");
}


/**
 * Função que salva a lista ligada em um arquivo binário.
 * 
 * \param lista
 * \param nomeArquivo
 * \return 
 */
bool salvarTransporteBinario(struct listatransporte* lista, char* nomeArquivo) {
    FILE* ficheiro = fopen(nomeArquivo, "wb");
    if (ficheiro == NULL) {
        //printf("Erro ao abrir arquivo para escrita.\n");
        return false;
    }

    // Escreve o número de transporte no arquivo
    int numTransporte = 0;
    struct listatransporte* atual = lista;
    while (atual != NULL) {
        numTransporte++;
        atual = atual->proximo;
    }
    fwrite(&numTransporte, sizeof(int), 1, ficheiro);

    // Escreve cada transporte no arquivo
    atual = lista;
    while (atual != NULL) {
        fwrite(atual, sizeof(struct Transporte), 1, ficheiro);
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
bool carregarTransporteBinario(struct listatransporte** lista, char* nomeArquivo) {
    FILE* ficheiro = fopen(nomeArquivo, "rb");
    if (ficheiro == NULL) {
        //printf("Erro ao abrir arquivo para leitura.\n");
        return false;
    }

    // Lê o número de transportes do arquivo
    int numTransporte;
    fread(&numTransporte ,sizeof(int), 1, ficheiro);

    // Lê cada transporte do arquivo e insere na lista ligada
    for (int i = 0; i < numTransporte; i++) {
        struct listatransporte* novo = (struct listatransporte*)malloc(sizeof(struct Transporte));
        fread(novo, sizeof(struct Transporte), 1, ficheiro);
        novo->proximo = *lista;
        *lista = novo;
    }

    fclose(ficheiro);
}