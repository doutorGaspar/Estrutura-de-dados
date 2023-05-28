/*****************************************************************//**
 * \file   FileGrafo.c
 * \brief  Funçoes para o Grafo
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
 * Função para criar um novo vértice no grafo.
 * 
 * \param localizacao
 * \param cliente
 * \param transporte
 * \return 
 */
Vertice* criarVertice(char localizacao[], cliente cliente, Transporte transporte) {
    // Aloca memória para um novo vértice
    Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
    // Verifica se a alocação de memória foi bem-sucedida
    if (novoVertice != NULL) {
        // Copia a localização para o campo localizacao do novo vértice
        strcpy(novoVertice->localizacao, localizacao);
        // Atribui a estrutura do cliente ao campo cliente do novo vértice
        novoVertice->cliente = cliente;
        // Atribui a estrutura do transporte ao campo transporte do novo vértice
        novoVertice->transporte = transporte;
        // Inicializa o campo arestas como NULL
        novoVertice->arestas = NULL;
        // Inicializa o campo próximo como NULL
        novoVertice->proximo = NULL;
    }
    // Retorna o ponteiro para o novo vértice criado
    return novoVertice;
}

/**
 * Função para criar uma nova aresta entre dois vértices.
 * 
 * \param destino
 * \param custo
 * \return 
 */
Aresta* criarAresta(Vertice* destino, double custo) {
    // Aloca memória para uma nova aresta
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    // Verifica se a alocação de memória foi bem-sucedida
    if (novaAresta != NULL) {
        // Atribui o vértice de destino ao campo destino da nova aresta
        novaAresta->destino = destino;
        // Atribui o custo ao campo custo da nova aresta
        novaAresta->custo = custo;
        // Inicializa o campo próxima como NULL
        novaAresta->proxima = NULL;
    }
    // Retorna o ponteiro para a nova aresta criada
    return novaAresta;
}


/**
 * Função para adicionar um vértice ao grafo.
 * 
 * \param grafo
 * \param novoVertice
 */
bool adicionarVertice(Grafo* grafo, Vertice* novoVertice) {
    // Verifica se a lista de vértices do grafo está vazia
    if (grafo->vertices == NULL) {
        grafo->vertices = novoVertice;  // Adiciona o novo vértice como o primeiro vértice da lista
    }
    else {
        // Percorre a lista de vértices até encontrar o último vértice
        Vertice* atual = grafo->vertices;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoVertice;  // Adiciona o novo vértice como o próximo vértice do último vértice
    }
}

/**
 * Função para adicionar uma aresta entre dois vértices.
 * 
 * \param origem
 * \param destino
 * \param custo
 */
bool adicionarAresta(Vertice* origem, Vertice* destino, double custo) {
    // Cria uma nova aresta com o vértice de destino e o custo especificados
    Aresta* novaAresta = criarAresta(destino, custo);
    if (novaAresta != NULL) {
        // Verifica se a lista de arestas do vértice de origem está vazia
        if (origem->arestas == NULL) {
            origem->arestas = novaAresta;  // Adiciona a nova aresta como a primeira aresta da lista
        }
        else {
            // Percorre a lista de arestas até encontrar a última aresta
            Aresta* atual = origem->arestas;
            while (atual->proxima != NULL) {
                atual = atual->proxima;
            }
            atual->proxima = novaAresta;  // Adiciona a nova aresta como a próxima aresta da última aresta
        }
    }
}


/**
 * Função para liberar a memória alocada pelo grafo.
 * 
 * \param grafo
 */
bool liberarGrafo(Grafo* grafo) {
    // Inicia o ponteiro atual com a lista de vértices do grafo
    Vertice* atual = grafo->vertices;
    // Percorre todos os vértices do grafo
    while (atual != NULL) {
        // Inicia o ponteiro arestaAtual com a lista de arestas do vértice atual
        Aresta* arestaAtual = atual->arestas;
        // Percorre todas as arestas do vértice atual
        while (arestaAtual != NULL) {
            // Armazena o ponteiro para a próxima aresta
            Aresta* proximaAresta = arestaAtual->proxima;
            // Libera a memória alocada para a aresta atual
            free(arestaAtual);
            // Atualiza o ponteiro para a próxima aresta
            arestaAtual = proximaAresta;
        }
        // Armazena o ponteiro para o próximo vértice
        Vertice* proximoVertice = atual->proximo;
        // Libera a memória alocada para o vértice atual
        free(atual);
        // Atualiza o ponteiro para o próximo vértice
        atual = proximoVertice;
    }
    // Define o ponteiro de vértices do grafo como NULL
    grafo->vertices = NULL;
}
/**
 * Funçao que salva o ficheiro grafo em txt.
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
        // Escreve a localização do vértice no arquivo
        fprintf(arquivo, "Localizacao: %s\n", atual->localizacao);
        // Escreve os dados do cliente no arquivo
        fprintf(arquivo, "Cliente: %s\n", atual->cliente.nome);
        // Escreve os dados do transporte no arquivo
        fprintf(arquivo, "Transporte: %s\n", atual->transporte.local);
        // Separador entre vértices
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
 * Funçao que salva o Ficheiro Grafo txt em binario.
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
        // Escreve a estrutura do vértice diretamente no arquivo
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
 * Função que encontra um vértice em um grafo pelo seu nome de localização.
 *
 * \param grafo O grafo onde será realizado a busca.
 * \param localizacao O nome de localização do vértice a ser encontrado.
 * \return O ponteiro para o vértice encontrado ou NULL se o vértice não for encontrado.
 */
Vertice* encontrarVertice(Grafo* grafo, const char* localizacao) {
    // Inicia o ponteiro atual com a lista de vértices do grafo
    Vertice* atual = grafo->vertices;
    // Percorre a lista de vértices
    while (atual != NULL) {
        // Compara o nome de localização do vértice atual com o localização fornecido
        if (strcmp(atual->localizacao, localizacao) == 0) {
            return atual;  // Retorna o vértice encontrado
        }
        // Atualiza o ponteiro para o próximo vértice
        atual = atual->proximo;
    }
    return NULL;  // Retorna NULL se o vértice não for encontradoo
}

/**
 * Função que cria um novo grafo.
 *
 * \return O ponteiro para o novo grafo criado.
 */
Grafo* criarGrafo() {
    // Aloca memória para a estrutura do grafo
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    // Verifica se a alocação foi bem-sucedida
    if (grafo != NULL) {
        grafo->vertices = NULL;  // Inicializa a lista de vértices como NULL
    }
    return grafo;  // Retorna o ponteiro para o novo grafo criado
}

/**
 * Funçao que carrega o ficheiro txt para binario do Grafo.
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
    // Variável auxiliar para ler os vértices do arquivo
    Vertice verticeAux;

    // Lê cada vértice do arquivo e adiciona ao grafo
    while (fread(&verticeAux, sizeof(Vertice), 1, arquivo) == 1) {
        // Cria um novo vértice com os dados lidos do arquivo
        Vertice* novoVertice = criarVertice(verticeAux.localizacao, verticeAux.cliente, verticeAux.transporte);
        // Adiciona o vértice ao grafo
        adicionarVertice(grafo, novoVertice);
        // Variável auxiliar para ler as arestas do arquivo
        Aresta arestaAux;
        // Lê cada aresta do arquivo e adiciona ao vértice correspondente
        while (fread(&arestaAux, sizeof(Aresta), 1, arquivo) == 1) {
            // Procura o vértice de destino no grafo
            Vertice* destino = encontrarVertice(grafo, arestaAux.destino->localizacao);

            // Adiciona a aresta ao vértice atual
            adicionarAresta(novoVertice, destino, arestaAux.custo);
        }
    }
    fclose(arquivo);
    return grafo;
}

#pragma region Exibicao
/**
 * Função para exibir as informações de todos os vértices e suas arestas no grafo.
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

