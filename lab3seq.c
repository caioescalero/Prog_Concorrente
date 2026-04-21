#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval inicio, fim;

#define TAMANHO 100000000

int main(){
    
    gettimeofday(&inicio, NULL);

    double *vetorA = malloc(sizeof(double) * TAMANHO);
    double *vetorB = malloc(sizeof(double) * TAMANHO);
    double soma_total = 0.0;

    for(int i = 0; i < TAMANHO; i++){
        vetorA[i] = 2.0;
        vetorB[i] = 1.0;
        soma_total += vetorA[i]*vetorB[i];
    }

    printf("soma total eh: %lf\n", soma_total);

    gettimeofday(&fim, NULL);

    double tempo = (fim.tv_sec - inicio.tv_sec) +
               (fim.tv_usec - inicio.tv_usec) / 1000000.0;

    printf("Tempo: %f segundos\n", tempo);
    return 0;
}