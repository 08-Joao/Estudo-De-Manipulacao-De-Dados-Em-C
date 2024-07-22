#include "funcionarios.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (func) {
        memset(func, 0, sizeof(TFunc));
        func->cod = cod;
        strcpy(func->nome, nome);
        strcpy(func->cpf, cpf);
        strcpy(func->data_nascimento, data_nascimento);
        func->salario = salario;
    }
    return func;
}

void salva(TFunc *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
    fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), out);
    fwrite(&func->salario, sizeof(double), 1, out);
}

TFunc *le(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (func && fread(&func->cod, sizeof(int), 1, in) > 0) {
        fread(func->nome, sizeof(char), sizeof(func->nome), in);
        fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
        fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
        fread(&func->salario, sizeof(double), 1, in);
        return func;
    }
    free(func);
    return NULL;
}

void imprime(TFunc *func) {
    printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("\nFuncionario de codigo %d\n", func->cod);
    printf("Nome: %s\n", func->nome);
    printf("CPF: %s\n", func->cpf);
    printf("Data de Nascimento: %s\n", func->data_nascimento);
    printf("Salario: %.2f\n", func->salario);
    printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
}

int tamanho_registro() {
    return sizeof(int) + sizeof(char) * 50 + sizeof(char) * 15 + sizeof(char) * 11 + sizeof(double);
}

int qtdRegistros(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq) / tamanho_registro();
    return tam;
}

void criarBaseOrdenada(FILE *out, int tam) {
    TFunc *f;
    for (int i = 0; i < tam; i++) {
        f = funcionario(i + 1, "A", "000.000.000-00", "01/01/1980", 3000 * i);
        salva(f, out);
        free(f);
    }
}

void embaralha(int *vet, int max, int trocas) {
    srand(time(NULL));
    for (int i = 0; i <= trocas; i++) {
        int j = rand() % (max - 1);
        int k = rand() % (max - 1);
        int tmp = vet[j];
        vet[j] = vet[k];
        vet[k] = tmp;
    }
}

void criarBaseDesordenada(FILE *out, int tam, int qtdTrocas) {
    int vet[tam];
    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;
    embaralha(vet, tam, qtdTrocas);
    TFunc *f;
    for (int i = 0; i < tam; i++) {
        f = funcionario(vet[i], "A", "000.000.000-00", "01/01/1980", 3000 * i);
        salva(f, out);
        free(f);
    }
}

TFunc *busca(FILE *in, int tam, int cod) {
    int comparacoes = 0;
    for (int i = 0; i < tam; i++) {
        fseek(in, tamanho_registro() * i, SEEK_SET);
        TFunc *f = le(in);
        comparacoes += 1;
        if (f != NULL && f->cod == cod) {
                printf("\nConseguimos achar o funcionario com a quantidade de %d comparacoes\n",comparacoes);
            return f;
        }
        free(f);
    }
    printf("\nNao conseguimos achar o funcionario, tivemos o total de %d comparacoes\n",comparacoes);
    return NULL;
}
TFunc *buscaBinaria(FILE *in, int tam, int cod) {
    int comparacoes = 0;
    int inicio = 0;
    int fim = tam - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;  // recalcula o índice do meio a cada iteração

        fseek(in, tamanho_registro() * meio, SEEK_SET);  // posiciona o cursor no registro do meio
        TFunc *f = le(in);  // lê o registro do arquivo
        comparacoes++;

        if (f->cod == cod) {
            printf("\nConseguimos achar o funcionario com a quantidade de %d comparacoes\n", comparacoes);
            return f;
        } else if (f->cod < cod) {
            inicio = meio + 1;  // ajusta os limites para a busca na metade superior
        } else {
            fim = meio - 1;  // ajusta os limites para a busca na metade inferior
        }

        // liberar memória alocada para o registro lido
        free(f);
    }

    printf("\nNao conseguimos achar o funcionario, tivemos o total de %d comparacoes\n", comparacoes);
    return NULL;
}



void imprimirBase(FILE *out) {
    printf("\nImprimindo a base de dados...\n");
    rewind(out);
    TFunc *f;
    while ((f = le(out)) != NULL) {
        imprime(f);
        free(f);
    }
}
