//Crie um programa que lê um vetor de 10 inteiros e imprime esses valores em ordem crescente. Obs: Os valores da resposta devem separados por espaços, na mesma linha. Ex: 1 2 3 4...

#include <stdio.h>

int main(){
int A[10],x;

for(int i=0;i<10;i++)
 scanf("%d",&A[i]);

for(int i=0;i<10;i++){
 for(int j=i+1;j<10;j++){
   if(A[i]>A[j]){
    x=A[i];
    A[i]=A[j];
    A[j]=x;
    }
   }
 }
for(int i=0;i<10;i++)
 printf(" %d",A[i]);
}
