//Crie uma função que recebe um inteiro N e um vetor de N elementos, e preenche o vetor com os N primeiros múltiplos de N.
//Exemplos: N=3 Vetor={3, 6, 9} / N=4 Vetor={4, 8, 12, 16}
//Crie um programa que lê um inteiro N, aloca dinamicamente um vetor de inteiros N, chama a função definida anteriormente e imprime o os N valores do vetor (separados por espaços) após executar a função.

#include <stdio.h>
#include <stdlib.h>

void multiplos(int x, int *y){
    int aux=1;
    for(int i=0; i<x; i++){
        y[i]=x*aux;
        aux++;
    }
}

int main(void){
    int num;
    scanf("%d",&num);
    int *vetor = (int *)malloc(num * sizeof (int));
    multiplos(num, &vetor[0]);
    for(int i=0; i<num; i++){
        printf("%d ",vetor[i]);
    }
    free(vetor);
    return 0;
}
