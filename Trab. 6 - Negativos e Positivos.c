//Crie uma função que recebe um vetor de 10 inteiros,
//transforma os valores negativos em positivos e retorna o vetor com as alterações.

//Crie um programa que lê um vetor de 10 inteiros, executa a função descrita anteriormente e imprime os valores do vetor (separados por espaços).

#include <stdio.h>
#include <stdlib.h>

void virav(int *x){
        for(int i=0;i<10;i++){
            if(x[i]<0){
                x[i]=(-1)*(x[i]);
            }
        }
}

int main (void){
    int v[10];
    for(int i=0;i<10;i++){
        scanf("%d",&v[i]);
    }
    virav(&v[0]);
    for(int i=0;i<10;i++){
        printf("%d ",v[i]);
    }
}
