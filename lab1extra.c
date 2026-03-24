/*
 * ------------------------------------------------------------
 * Autor: Caio Escalero
 * Disciplina: Programação Concorrente
 *
 * Descrição:
 * Programa em C que utiliza múltiplas threads (pthread)
 * para calcular a soma de um vetor de inteiros.
 *
 * O vetor é dividido em partes iguais entre as threads.
 * Cada thread calcula a soma parcial do seu segmento e
 * retorna o resultado para a thread principal.
 *
 * A thread principal coleta os resultados parciais e
 * calcula a soma total do vetor.
 *
 * Parâmetros de entrada:
 *   argv[1] -> número de threads
 *   argv[2] -> tamanho do vetor
 *
 * Exemplo de execução:
 *   ./programa 4 1000
 *
 * Saída:
 *   Soma parcial de cada thread
 *   Soma total do vetor
 *
 * Observações:
 * - Não utiliza mutex (cada thread opera em uma região distinta)
 * - Uso de alocação dinâmica para retorno das threads
 * ------------------------------------------------------------
 */

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
