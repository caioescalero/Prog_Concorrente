#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

struct timeval inicio, fim;

#define TAMANHO 100000000

typedef struct{
    int inicio, fim, id;
    double *vetorA, *vetorB, soma;
} t_Thread;

void* produto_interno(void* arg){
    t_Thread* args = (t_Thread*) arg;
    for(int i = args->inicio; i < args->fim; i++){
        args->vetorA[i] = 2.0;
        args->vetorB[i] = 1.0;
        args->soma += args->vetorA[i]*args->vetorB[i];
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    gettimeofday(&inicio, NULL);
    if(argc < 2) {
        printf("--ERRO: informe <%s> <nthreads>\n", argv[0]);
            return 1;
    }
    int nthreads = atoi(argv[1]);
    int bloco = TAMANHO/nthreads;

    pthread_t tid[nthreads];
    t_Thread args[nthreads];

    double *vetorA = malloc(sizeof(double) * TAMANHO);
    double *vetorB = malloc(sizeof(double) * TAMANHO);
    double soma_total = 0.0;

     for(int i = 0; i < nthreads; i++){
        if(i == nthreads - 1 && TAMANHO % nthreads != 0){
            args[i].inicio = i*bloco;
            args[i].fim = TAMANHO;
            args[i].id = i;
            args[i].soma = 0.0;
            args[i].vetorA = vetorA;
            args[i].vetorB = vetorB;
        }
        else{
            args[i].inicio = i*bloco;
            args[i].fim = (i+1)*bloco;
            args[i].id = i;
            args[i].soma = 0.0;
            args[i].vetorA = vetorA;
            args[i].vetorB = vetorB;
        }
        pthread_create(&tid[i], NULL, produto_interno, &args[i]);
        printf("thread %d criada\n", i);
    }

    for(int i = 0; i < nthreads; i++){
        pthread_join(tid[i], NULL);
        soma_total += args[i].soma;
    }

    printf("produto interno eh: %lf\n", soma_total);
    printf("fim da thread principal\n");

    gettimeofday(&fim, NULL);

    double tempo = (fim.tv_sec - inicio.tv_sec) +
               (fim.tv_usec - inicio.tv_usec) / 1000000.0;

    printf("Tempo: %f segundos\n", tempo);
    return 0;
}