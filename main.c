#include <stdio.h>
#include <stdlib.h>
#include "funcionarios.h"
#include <time.h>

int main() {
    FILE *out;

    if ((out = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    // Posiciona o cursor no início do arquivo
    rewind(out);

    // Criando base de dados ordenada
    printf("\nCriando base ordenada de dados... 1\n");
    criarBaseOrdenada(out, 120000);
    clock_t start, end;
    start = clock();
    printf("\nRealizando busca sequencial...\n");
    TFunc *f = busca(out, 120000, 36475);
    if (f != NULL) {
        imprime(f);
        free(f);
    }
    end = clock();
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC);
    printf("Tempo de execucao: %f.\n", time_taken);

    rewind(out);
/*
    // Criando uma segunda base de dados ordenada
    printf("\nCriando base ordenada de dados... 2\n");
    criarBaseOrdenada(out, 38);
    start = clock();
    f = busca(out, 38, 5);
    if (f != NULL) {
        imprime(f);
        free(f);
    }
    end = clock();
    double time_taken_3 = ((double)(end - start) / CLOCKS_PER_SEC);
    printf("Tempo de execucao da segunda base ordenada: %f.\n", time_taken_3);

    rewind(out);

    // Criando a primeira base de dados desordenada
     printf("\nCriando base desordenada de dados... 1\n");
    criarBaseDesordenada(out, 120000, 9541);
    start = clock();
    f = busca(out, 100000, 84315);
    if (f != NULL) {
        imprime(f);

        free(f);
    }
    end = clock();
    double time_taken_2 = ((double)(end - start) / CLOCKS_PER_SEC);
    printf("Tempo de execucao da base desordenada: %f.\n", time_taken_2);

    rewind(out);

    // Criando a segunda base de dados desordenada (ajustado para um tamanho razoável)
     printf("\nCriando base desordenada de dados... 2\n");
    criarBaseDesordenada(out, 200000, 1750);
    start = clock();
    f = busca(out, 1000000, 417);
    if (f != NULL) {
        imprime(f);
        free(f);
    }
    end = clock();
    double time_taken_4 = ((double)(end - start) / CLOCKS_PER_SEC);
    printf("Tempo de execucao da segunda base desordenada: %f.\n", time_taken_4);
    */

    rewind(out);
    printf("\nRealizando busca binaria...\n");
    start = clock();
    f = buscaBinaria(out, 120000, 36475);
        if (f != NULL) {
        imprime(f);
        free(f);
    }
    end = clock();
    time_taken = ((double)(end - start) / CLOCKS_PER_SEC);
    printf("Tempo de execucao: %f.\n", time_taken);
    fclose(out);

    return 0;
}
