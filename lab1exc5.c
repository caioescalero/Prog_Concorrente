/* Disciplina: Programacao Concorrente */
/* Profa.: Silvana Rossetto */
/* Laboratório: 1 */
/* Codigo: "Hello World" usando threads em C e a funcao que espera as threads terminarem */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//cria a estrutura de dados para armazenar os argumentos da thread
typedef struct {
   int inicio;
   int fim;
   int *vetor;
} t_Args;

//funcao executada pelas threads
void *Incrementa (void *arg) {
  t_Args *args = (t_Args *) arg;
  for(int i = args->inicio; i < args->fim; i++){
    args->vetor[i]++;
  }
  free(arg); //libera a alocacao feita na main

  pthread_exit(NULL);
}

//funcao principal do programa
int main(int argc, char* argv[]) {
  t_Args *args; //receberá os argumentos para a thread

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

  puts("Vetor Antigo:\n");
  for(int i = 0; i < tam_vetor; i++){
    vetor[i] = i;
    printf("%d ", vetor[i]);
  }
  puts("\n");

  //identificadores das threads no sistema
  pthread_t tid_sistema[num_threads];

  //cria as threads
  for(int i = 0; i < num_threads; i++) {
    printf("\n--Aloca e preenche argumentos para thread %d\n", i);
    args = malloc(sizeof(t_Args));
    
    if (args == NULL) {
      printf("--ERRO: malloc()\n");
      return 1;
    }

    //caso a divisão não seja exata o último thread fica com o resto do vetor
    if(tam_vetor % num_threads != 0 && i == num_threads - 1){
      args->inicio = i*bloco;
      args->fim = tam_vetor;
      args->vetor = vetor;
    }

    else{
        args->inicio = i*bloco;
        args->fim = (i+1)*bloco;
        args->vetor = vetor;
    }

    printf("--Cria a thread %d\n", i);
    if (pthread_create(&tid_sistema[i], NULL, Incrementa, (void*) args)) {
      printf("--ERRO: pthread_create()\n");
      return 2;
    }
  }

  //espera todas as threads terminarem
  for (int i = 0; i < num_threads; i++) {
    if (pthread_join(tid_sistema[i], NULL)) {
         printf("--ERRO: pthread_join() da thread %d\n", i);
    }
  }

  //log da função principal
  printf("--Thread principal terminou\n");

  puts("\nVetor Novo:\n");
  for(int i = 0; i < tam_vetor; i++){
    printf("%d ", vetor[i]);
  }
}