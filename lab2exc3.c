/* Disciplina: Programacao Concorrente */
/* Profa.: Silvana Rossetto */
/* Laboratório: 1 */
/* Codigo: "Hello World" usando threads em C com passagem de um argumento */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAMANHOS

typedef struct{
    int id;
} t_Threads;

//--funcao executada pelas threads
void *PrintHello (void* arg) {
    t_Threads *args = (t_Threads*) arg;
   printf("Hello World da thread: %d\n", args->id);

   pthread_exit(NULL);
}

//--funcao principal do programa
int main(int argc, char * argv[]) {
   int nthreads; //qtde de threads que serao criadas (recebida na linha de comando)

   //verifica se o argumento 'qtde de threads' foi passado e armazena seu valor
   if(argc<2) {
       printf("--ERRO: informe a qtde de threads <%s> <nthreads>\n", argv[0]);
       return 1;
   }
   nthreads = atoi(argv[1]);

   //identificadores das threads no sistema
   pthread_t tid[nthreads];
   t_Threads args[nthreads];

#ifdef TAMANHOS
   //exibe os tamanhos dos tipos - para informacao apenas
   puts("Tamanhos dos tipos de dados:");
   printf("Tamanho ponteiro:%ld bytes\n", sizeof(void*));
   printf("Tamanho int:%ld bytes\n", sizeof(int));
   printf("Tamanho long int:%ld bytes\n\n", sizeof(long int));
#endif

   //cria as threads e atribui a tarefa de cada thread
   for(long int i=0; i<nthreads; i++) {
    args[i].id = i;
      printf("--Cria a thread %ld\n", i);
      if (pthread_create(&tid[i], NULL, PrintHello, (void*) &args[i])) {
         printf("--ERRO: pthread_create()\n");
	       return 2;
      }
   }

   for(int i = 0; i < nthreads; i++){
    pthread_join(tid[i], NULL);
    printf("thread %d finalizada\n", i); //pthread_join garantindo que todas as threads sejam encerradas antes da main
   }
   //log da função main
   printf("--Thread principal terminou\n");
   return 0;
}