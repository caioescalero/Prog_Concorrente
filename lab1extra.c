#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int *vetor;
    int inicio;
    int fim;
    int soma;
    int quem_sou;
} t_Thread;

void *soma(void* arg){
    t_Thread *args = (t_Thread*) arg;
    for(int i = args->inicio; i < args->fim; i++){
        args->soma += args->vetor[i];
    }
    printf("soma da thread %d eh: %d\n", args->quem_sou, args->soma);
    int *ret = malloc(sizeof(int));
    *ret = args->soma;
    free(arg);
    pthread_exit((void*) ret);
}

int main(int argc, char* argv[]) {
  t_Thread *args; //receberá os argumentos para a thread

  int num_threads; //qtde de threads que serao criadas (recebida na linha de comando)

  //verifica se o argumento 'qtde de threads' foi passado e armazena seu valor
  if(argc < 3) {
    printf("--ERRO: informe <%s> <nthreads> <tam_vetor>\n", argv[0]);
    return 1;
}

  num_threads = atoi(argv[1]);
  int tam_vetor = atoi(argv[2]);
  int vetor[tam_vetor];
  int bloco = tam_vetor/num_threads;
  int soma_total = 0;
  void *retorno;

  for(int i = 0; i < tam_vetor; i++){
    vetor[i] = i;
  }

  pthread_t identificador[num_threads];
  for(int i = 0; i < num_threads; i++){
    args = malloc(sizeof(t_Thread));

    if(tam_vetor % num_threads != 0 && i == num_threads - 1){
        args->inicio = i*bloco;
        args->fim = tam_vetor;
        args->vetor = vetor;
        args->soma = 0;
        args->quem_sou = i;
    }
    else{
        args->inicio = i*bloco;
        args->fim = (i+1)*bloco;
        args->vetor = vetor;
        args->soma = 0;
        args->quem_sou = i;
    }

    pthread_create(&identificador[i], NULL, soma, (void*) args);
  }

   for(int i = 0; i < num_threads; i++){
    pthread_join(identificador[i], &retorno);
    soma_total += *((int*)retorno);
    free(retorno);
   }
    printf("resultado final: %d\n", soma_total);
 puts("thread principal acabou\n");
}