/*****************************************************************//**
 * \file   FileGrafo.c
 * \brief  Fun�oes para o Grafo
 * 
 * \author gaspar
 * \date   May 2023
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"
#pragma warning(disable : 4996)

/**
 * Fun��o para criar um novo v�rtice no grafo.
 * 
 * \param localizacao
 * \param cliente
 * \param transporte
 * \return 
 */
Vertice* criarVertice(char localizacao[], cliente cliente, Transporte transporte) {
    // Aloca mem�ria para um novo v�rtice
    Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
    // Verifica se a aloca��o de mem�ria foi bem-sucedida
    if (novoVertice != NULL) {
        // Copia a localiza��o para o campo localizacao do novo v�rtice
        strcpy(novoVertice->localizacao, localizacao);
        // Atribui a estrutura do cliente ao campo cliente do novo v�rtice
        novoVertice->cliente = cliente;
        // Atribui a estrutura do transporte ao campo transporte do novo v�rtice
        novoVertice->transporte = transporte;
        // Inicializa o campo arestas como NULL
        novoVertice->arestas = NULL;
        // Inicializa o campo pr�ximo como NULL
        novoVertice->proximo = NULL;
    }
    // Retorna o ponteiro para o novo v�rtice criado
    return novoVertice;
}

/**
 * Fun��o para criar uma nova aresta entre dois v�rtices.
 * 
 * \param destino
 * \param custo
 * \return 
 */
Aresta* criarAresta(Vertice* destino, double custo) {
    // Aloca mem�ria para uma nova aresta
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    // Verifica se a aloca��o de mem�ria foi bem-sucedida
    if (novaAresta != NULL) {
        // Atribui o v�rtice de destino ao campo destino da nova aresta
        novaAresta->destino = destino;
        // Atribui o custo ao campo custo da nova aresta
        novaAresta->custo = custo;
        // Inicializa o campo pr�xima como NULL
        novaAresta->proxima = NULL;
    }
    // Retorna o ponteiro para a nova aresta criada
    return novaAresta;
}


/**
 * Fun��o para adicionar um v�rtice ao grafo.
 * 
 * \param grafo
 * \param novoVertice
 */
bool adicionarVertice(Grafo* grafo, Vertice* novoVertice) {
    // Verifica se a lista de v�rtices do grafo est� vazia
    if (grafo->vertices == NULL) {
        grafo->vertices = novoVertice;  // Adiciona o novo v�rtice como o primeiro v�rtice da lista
    }
    else {
        // Percorre a lista de v�rtices at� encontrar o �ltimo v�rtice
        Vertice* atual = grafo->vertices;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoVertice;  // Adiciona o novo v�rtice como o pr�ximo v�rtice do �ltimo v�rtice
    }
}

/**
 * Fun��o para adicionar uma aresta entre dois v�rtices.
 * 
 * \param origem
 * \param destino
 * \param custo
 */
bool adicionarAresta(Vertice* origem, Vertice* destino, double custo) {
    // Cria uma nova aresta com o v�rtice de destino e o custo especificados
    Aresta* novaAresta = criarAresta(destino, custo);
    if (novaAresta != NULL) {
        // Verifica se a lista de arestas do v�rtice de origem est� vazia
        if (origem->arestas == NULL) {
            origem->arestas = novaAresta;  // Adiciona a nova aresta como a primeira aresta da lista
        }
        else {
            // Percorre a lista de arestas at� encontrar a �ltima aresta
            Aresta* atual = origem->arestas;
            while (atual->proxima != NULL) {
                atual = atual->proxima;
            }
            atual->proxima = novaAresta;  // Adiciona a nova aresta como a pr�xima aresta da �ltima aresta
        }
    }
}


/**
 * Fun��o para liberar a mem�ria alocada pelo grafo.
 * 
 * \param grafo
 */
bool liberarGrafo(Grafo* grafo) {
    // Inicia o ponteiro atual com a lista de v�rtices do grafo
    Vertice* atual = grafo->vertices;
    // Percorre todos os v�rtices do grafo
    while (atual != NULL) {
        // Inicia o ponteiro arestaAtual com a lista de arestas do v�rtice atual
        Aresta* arestaAtual = atual->arestas;
        // Percorre todas as arestas do v�rtice atual
        while (arestaAtual != NULL) {
            // Armazena o ponteiro para a pr�xima aresta
            Aresta* proximaAresta = arestaAtual->proxima;
            // Libera a mem�ria alocada para a aresta atual
            free(arestaAtual);
            // Atualiza o ponteiro para a pr�xima aresta
            arestaAtual = proximaAresta;
        }
        // Armazena o ponteiro para o pr�ximo v�rtice
        Vertice* proximoVertice = atual->proximo;
        // Libera a mem�ria alocada para o v�rtice atual
        free(atual);
        // Atualiza o ponteiro para o pr�ximo v�rtice
        atual = proximoVertice;
    }
    // Define o ponteiro de v�rtices do grafo como NULL
    grafo->vertices = NULL;
}
/**
 * Fun�ao que salva o ficheiro grafo em txt.
 * 
 * \param grafo
 * \param nomeArquivo
 * \return 
 */
bool salvarGrafoTexto(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        //printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        // Escreve a localiza��o do v�rtice no arquivo
        fprintf(arquivo, "Localizacao: %s\n", atual->localizacao);
        // Escreve os dados do cliente no arquivo
        fprintf(arquivo, "Cliente: %s\n", atual->cliente.nome);
        // Escreve os dados do transporte no arquivo
        fprintf(arquivo, "Transporte: %s\n", atual->transporte.local);
        // Separador entre v�rtices
        fprintf(arquivo, "-----\n");
        Aresta* arestaAtual = atual->arestas;
        while (arestaAtual != NULL) {
            // Escreve o destino da aresta no arquivo
            fprintf(arquivo, "Aresta para: %s\n", arestaAtual->destino->localizacao);
            // Escreve o custo da aresta no arquivo
            fprintf(arquivo, "Custo: %lf\n", arestaAtual->custo);
            // Separador entre arestas
            fprintf(arquivo, "-----\n");

            arestaAtual = arestaAtual->proxima;
        }
        atual = atual->proximo;
    }
    fclose(arquivo);
}
/**
 * Fun�ao que salva o Ficheiro Grafo txt em binario.
 * 
 * \param grafo
 * \param nomeArquivo
 * \return 
 */
bool salvarGrafoBinario(Grafo* grafo, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        //printf("Erro ao abrir o arquivo.\n");
        return false;
    }
    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        // Escreve a estrutura do v�rtice diretamente no arquivo
        fwrite(atual, sizeof(Vertice), 1, arquivo);

        Aresta* arestaAtual = atual->arestas;
        while (arestaAtual != NULL) {
            // Escreve a estrutura da aresta diretamente no arquivo
            fwrite(arestaAtual, sizeof(Aresta), 1, arquivo);
            arestaAtual = arestaAtual->proxima;
        }
        atual = atual->proximo;
    }
    fclose(arquivo);
}

/**
 * Fun��o que encontra um v�rtice em um grafo pelo seu nome de localiza��o.
 *
 * \param grafo O grafo onde ser� realizado a busca.
 * \param localizacao O nome de localiza��o do v�rtice a ser encontrado.
 * \return O ponteiro para o v�rtice encontrado ou NULL se o v�rtice n�o for encontrado.
 */
Vertice* encontrarVertice(Grafo* grafo, const char* localizacao) {
    // Inicia o ponteiro atual com a lista de v�rtices do grafo
    Vertice* atual = grafo->vertices;
    // Percorre a lista de v�rtices
    while (atual != NULL) {
        // Compara o nome de localiza��o do v�rtice atual com o localiza��o fornecido
        if (strcmp(atual->localizacao, localizacao) == 0) {
            return atual;  // Retorna o v�rtice encontrado
        }
        // Atualiza o ponteiro para o pr�ximo v�rtice
        atual = atual->proximo;
    }
    return NULL;  // Retorna NULL se o v�rtice n�o for encontradoo
}

/**
 * Fun��o que cria um novo grafo.
 *
 * \return O ponteiro para o novo grafo criado.
 */
Grafo* criarGrafo() {
    // Aloca mem�ria para a estrutura do grafo
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    // Verifica se a aloca��o foi bem-sucedida
    if (grafo != NULL) {
        grafo->vertices = NULL;  // Inicializa a lista de v�rtices como NULL
    }
    return grafo;  // Retorna o ponteiro para o novo grafo criado
}

/**
 * Fun�ao que carrega o ficheiro txt para binario do Grafo.
 * 
 * \param nomeArquivo
 * \return 
 */
Grafo* carregarGrafoBinario(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        //printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }
    Grafo* grafo = criarGrafo();
    // Vari�vel auxiliar para ler os v�rtices do arquivo
    Vertice verticeAux;

    // L� cada v�rtice do arquivo e adiciona ao grafo
    while (fread(&verticeAux, sizeof(Vertice), 1, arquivo) == 1) {
        // Cria um novo v�rtice com os dados lidos do arquivo
        Vertice* novoVertice = criarVertice(verticeAux.localizacao, verticeAux.cliente, verticeAux.transporte);
        // Adiciona o v�rtice ao grafo
        adicionarVertice(grafo, novoVertice);
        // Vari�vel auxiliar para ler as arestas do arquivo
        Aresta arestaAux;
        // L� cada aresta do arquivo e adiciona ao v�rtice correspondente
        while (fread(&arestaAux, sizeof(Aresta), 1, arquivo) == 1) {
            // Procura o v�rtice de destino no grafo
            Vertice* destino = encontrarVertice(grafo, arestaAux.destino->localizacao);

            // Adiciona a aresta ao v�rtice atual
            adicionarAresta(novoVertice, destino, arestaAux.custo);
        }
    }
    fclose(arquivo);
    return grafo;
}

#pragma region Exibicao
/**
 * Fun��o para exibir as informa��es de todos os v�rtices e suas arestas no grafo.
 * 
 * \param grafo
 */
bool exibirGrafo(Grafo* grafo) {
    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        printf("Localizacao: %s\n", atual->localizacao);
        printf("Cliente: %s\n", atual->cliente.nome);
        printf("Meio de Transporte: %s\n", atual->transporte.tipo);

        Aresta* arestaAtual = atual->arestas;
        while (arestaAtual != NULL) {
            printf("  -> Destino: %s, Custo: %.2f\n", arestaAtual->destino->localizacao, arestaAtual->custo);
            arestaAtual = arestaAtual->proxima;
        }

        atual = atual->proximo;
        printf("\n");
    }
}
#pragma endregion

