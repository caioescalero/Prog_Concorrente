#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct{
    int *vetor, inicio, fim, soma, id, nthreads;
} t_Thread;

void* soma_vetor(void* arg){
    t_Thread *args = (t_Thread*) arg;
    for(int i = args->inicio; i < args->fim; i += args->nthreads){
        args->vetor[i]++;
        args->soma += args->vetor[i];
    }

    printf("thread %d concluida\n", args->id);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    int nthreads;
    int tam_vetor;
    int soma_total = 0;

     if(argc < 3) {
    printf("--ERRO: informe <%s> <nthreads> <tam_vetor>\n", argv[0]);
    return 1;
}
    
    nthreads = atoi(argv[1]);
    tam_vetor = atoi(argv[2]);
    int *vetor = malloc(sizeof(int) * tam_vetor);

    pthread_t tid[nthreads];
    t_Thread args[nthreads];

    puts("Vetor Antigo:\n");
    for(int i = 0; i < tam_vetor; i++){
        vetor[i] = i;
        printf("%d ", vetor[i]);
    }
    printf("\n");

    for(int i = 0; i < nthreads; i++){
        args[i].inicio = i;
        args[i].fim = tam_vetor;
        args[i].soma = 0;
        args[i].id = i;
        args[i].vetor = vetor;
        args[i].nthreads = nthreads;
        pthread_create(&tid[i], NULL, soma_vetor, &args[i]);
    }

    for(int i = 0; i < nthreads; i++){
        pthread_join(tid[i], NULL);
        soma_total += args[i].soma;
    }

    printf("Vetor Novo:\n");
    for(int i = 0; i < tam_vetor; i++){
        printf("%d ", vetor[i]);
    }

    printf("\n");
    printf("Soma do vetor eh: %d\n", soma_total);
    printf("final thread principal\n");
    return 0;
}