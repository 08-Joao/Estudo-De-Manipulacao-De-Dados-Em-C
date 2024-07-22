#ifndef FUNCIONARIOS_H_INCLUDED
#define FUNCIONARIOS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario);

void salva(TFunc *func, FILE *out);

TFunc *le(FILE *in);

void imprime(TFunc *func);

int tamanho_registro();

int qtdRegistros(FILE *arq);

void criarBaseOrdenada(FILE *out, int tam);

void criarBaseDesordenada(FILE *out, int tam, int qtdTrocas);


void imprimirBase(FILE *out);

TFunc *busca(FILE *in, int tam, int cod);

TFunc *buscaBinaria(FILE *in, int tam, int cod);

#endif // FUNCIONARIOS_H_INCLUDED
