/*****************************************************************//**
 * \file   FileTransporte.c
 * \brief  Fun�oes para o transporte
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
 * Fun��o que insere um novo transporte na lista ligada.
 * 
 * \param lista
 * \param elemento
 * \return 
 */
bool inserirElemento(listatransporte* lista, Transporte elemento) {
    listatransporte* novoElemento = (listatransporte*)malloc(sizeof(listatransporte));
    if (novoElemento == NULL) {
        return false;  // Falha na aloca��o de mem�ria
    }
    novoElemento->t = elemento;
    novoElemento->proximo = lista->primeiro;
    lista->primeiro = novoElemento;
    lista->tamanho++;
    return true;  // Inser��o bem-sucedida
}
/**
 * Fun��o que remove um transporte na lista ligada.
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
 * Fun��o que altere um transporte na lista ligada.
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
 * Fun�ao assistente a ordem decrescente de autonomia.
 * 
 * \param transport1
 * \param transport2
 */
void TrocarT(listatransporte* transport1, listatransporte* transport2) {
    // Armazena as informa��es do primeiro n� em uma vari�vel auxiliar
    Transporte aux = transport1->t;
    // Copia as informa��es do segundo n� para o primeiro n�
    transport1->t = transport2->t;
    // Copia as informa��es armazenadas na vari�vel auxiliar para o segundo n�
    transport2->t = aux;
}

/**
 * Fun��o que ordena uma lista ligada de transportes em ordem decrescente de autonomia.
 * A fun��o utiliza o algoritmo de ordena��o conhecido como Bubble Sort para ordenar
 * os transportes com base no valor da autonomia. A ordena��o � realizada em ordem decrescente.
 * 
 * \param head Ponteiro para o in�cio da lista ligada de transportes.
 * \return true se a ordena��o foi realizada com sucesso, false caso contr�rio.
 */
bool ordemDecrescenteAutonomia(listatransporte* head) {
    if (head == NULL) return false;

    bool isSorted = false; // Vari�vel de controle para verificar se a lista est� ordenada
    listatransporte* current = NULL;// Ponteiro para o elemento atual da lista
    // Loop principal do algoritmo
    while (!isSorted)
    {
        isSorted = true;
        current = head;
        // Loop para percorrer a lista e comparar elementos adjacentes
        while (current->proximo != NULL)
        {
            // Verifica se o elemento atual tem autonomia menor que o pr�ximo elemento
            if (current->t.autonimia < current->proximo->t.autonimia) {
                TrocarT(current, current->proximo);// Fun��o auxiliar para trocar os elementos
                isSorted = false; // A lista ainda n�o est� totalmente ordenada
            }
            current = current->proximo;
        }
    }
    return true;// Retorna true para indicar que a ordena��o foi conclu�da com sucesso
}

/**
 * Geocodigo
 * Fun��o que lista os transportes por localiza��o.
 * A fun��o percorre uma lista ligada de transportes e cria uma nova lista ligada contendo
 * apenas os transportes cuja localiza��o corresponde � localiza��o especificada.
 * \param head Ponteiro para o in�cio da lista ligada de transportes.
 * \param localizacao String contendo a localiza��o desejada.
 * \return Ponteiro para o in�cio da nova lista ligada contendo os transportes encontrados
 */

listatransporte* listarTransportePorLocalizacao(listatransporte* head, char* localizacao) {
    // Verifica se a lista est� vazia
    if (head == NULL)
        return NULL;

    listatransporte* ultimoAutomovel = NULL;  // Ponteiro para o �ltimo elemento da nova lista
    listatransporte* novaLista = NULL;  // Ponteiro para o in�cio da nova lista
    listatransporte* aux = head;  // Ponteiro auxiliar para percorrer a lista original

    while (aux != NULL) {
        // Verifica se a localiza��o do transporte corresponde � localiza��o desejada
        if (strcmp(aux->t.local, localizacao) == 0) {
            // Cria um novo elemento da lista para o transporte encontrado
            listatransporte* novoAutomovel = (listatransporte*)malloc(sizeof(listatransporte));
            novoAutomovel->t = aux->t;
            novoAutomovel->proximo = NULL;

            if (novaLista == NULL) {
                // Se for o primeiro elemento da nova lista, define-o como o in�cio
                novaLista = novoAutomovel;
                ultimoAutomovel = novaLista;
            }
            else {
                // Caso contr�rio, adiciona o novo elemento no final da nova lista
                ultimoAutomovel->proximo = novoAutomovel;
                ultimoAutomovel = novoAutomovel;
            }
        }
        aux = aux->proximo;
    }

    return novaLista;  // Retorna o ponteiro para o in�cio da nova lista ligada
}

/**
 * Fun�ao para o Registo do aluguer de um transporte.
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
                // Verificar se o meio de transporte existe e est� dispon�vel para aluguer
                struct listatransporte* transporteAtual = lista_transportes;
                while (transporteAtual != NULL) {
                    if (strcmp(transporteAtual->t.local, localTransporte) == 0) {
                        if (transporteAtual->t.alugado) {
                            //printf("Meio de transporte indispon�vel para aluguer.\n");
                            return;
                        }
                        else {
                            // Registar o aluguer do cliente
                            clienteAtual->c.saldoConta -= transporteAtual->t.custo;
                            // Marcar o meio de transporte como alugado
                            transporteAtual->t.alugado = true;
                            //printf("Aluguer registado com sucesso.\n");
                            return;
                        }
                    }
                    transporteAtual = transporteAtual->proximo;
                }
                //printf("Meio de transporte nao encontrado.\n");
                return;
            }
            else {
                //printf("Saldo insuficiente na conta do cliente.\n");
                return;
            }
        }
        clienteAtual = clienteAtual->proximo;
    }

    // Cliente n�o encontrado
    //printf("Cliente nao encontrado.\n");
    return false;
}


/**
 * Fun��o que salva a lista ligada em um arquivo bin�rio.
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

    // Escreve o n�mero de transporte no arquivo
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
 * Fun��o que l� a lista ligada de um arquivo bin�rio.
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

    // L� o n�mero de transportes do arquivo
    int numTransporte;
    fread(&numTransporte ,sizeof(int), 1, ficheiro);

    // L� cada transporte do arquivo e insere na lista ligada
    for (int i = 0; i < numTransporte; i++) {
        struct listatransporte* novo = (struct listatransporte*)malloc(sizeof(struct Transporte));
        fread(novo, sizeof(struct Transporte), 1, ficheiro);
        novo->proximo = *lista;
        *lista = novo;
    }

    fclose(ficheiro);
}