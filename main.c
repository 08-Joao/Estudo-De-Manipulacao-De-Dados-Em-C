#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcionarios.h"

int main(){
    FILE *out;
    printf("\nTeste 0\n");
    if ((out = fopen("funcionario.dat", "w+b")) == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
        return 1;
    }
    printf("\nTeste 1\n");

    FILE *log;

    if ((log = fopen("log.txt", "a")) == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
        return 1;
    }

    // posiciona o cursor no inicio do arquivo
    rewind(out);

    TFunc *f;

   rewind(out);


    printf("\nBusca Binaria\n");
    criarBaseDesordenada(out,5000,100);
    clock_t start,end;
    start = clock();
    insertionSort(out,5000, log);
    f = buscaBinaria(out,5000, 347); //Faz a busca binaria

    printf("\nTeste 5\n");
    if(f!=NULL){
        imprime(f);
    }
    end = clock();
    double time_taken2 = ((double)(end-start)/CLOCKS_PER_SEC);
    printf("O tempo de execucao foi de %f segundos.\n ",time_taken2);
    fprintf(log, "\nO tempo de execucao da busca + ordenacao e de: %f", time_taken2);


    fclose(out);
    fclose(log);
    return 0;
}
