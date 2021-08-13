//Criar um programa que lê um número e gera todos os números primos entre 1 e o número fornecido pelo usuário, escrevendo na tela o resultado.

//Obs: criar uma função que verifica se um número é primo para uso no programa.

//Exemplo: Entrada: 5 Saída: 2 3 5



#include <stdio.h>

int primos(int a){
for(int b=2;b<a;b++){
 if((a%b==0)){
  return 0;
  }
 }
printf(" %d",a);
return 0;
}

int varrer(int a){
 for(int b=2;b<=a;b++){
  primos(b);
 }
return 0;
}

int main (void){
float x;
scanf("%f",&x);
while(x<2){
 scanf("%f",&x);
 }
varrer(x);
}
