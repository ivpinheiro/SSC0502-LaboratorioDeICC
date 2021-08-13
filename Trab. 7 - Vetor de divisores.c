//Crie uma função que recebe um inteiro (N) e um ponteiro para vetor. A função deve preencher o vetor com os primeiros 20 divisores de N e retornar o vetor e o número de divisores inseridos no vetor.
//Crie um programa que lê um inteiro, cria um vetor de 20 inteiros, chama a função descrita anteriormente e imprime os valores válidos presentes no vetor em ordem decrescente, separados por espaços.

#include <stdio.h>
#include <stdlib.h>

void divisor(int x, int *y, int *z){
    int div=x-1;
    while(*z<20){
        if(div==0){
            break;
        }
        if(x%div==0){
            y[*z]=div;
            (*z)++;
        }
        div--;
    }
}

int main(void){
    int num, vetor[20],aux=0;
    scanf("%d",&num);
    divisor(num,&vetor[0],&aux);
    for(int i=0; i<aux; i++){
        printf("%d ",vetor[i]);
    }
    return 0;
}
